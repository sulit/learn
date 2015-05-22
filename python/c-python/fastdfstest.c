#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fdfs_client.h"
#include "fdfs_global.h"
#include "base64.h"
#include "sockopt.h"
#include "logger.h"
#include "fdfs_http_shared.h"

static int fdfs_init(const char *conf_filename);
static int writeToFileCallback(void *arg, const int64_t file_size,
			const char *data, const int current_size);
static int uploadFileCallback(void *arg, const int64_t file_size, int sock);


static PyObject *fdfs_upload(PyObject *self, PyObject *args)
{
	char *conf_filename;
	char *local_filename;
	char *upload_typestr;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	char remote_filename[256];
	char master_filename[256];
	FDFSMetaData meta_list[32];
	int meta_count;
	char token[32 + 1];
	char file_id[128];
	char file_url[256];
	char szDatetime[20];
	char szPortPart[16];
	int url_len;
	time_t ts;
	int64_t file_size;
	int store_path_index;
	FDFSFileInfo file_info;

	if (!PyArg_ParseTuple(args, "ssz",  &conf_filename, &local_filename, &upload_typestr))
		return NULL;

	if ((result = fdfs_init(conf_filename)) != 0) {
		return Py_BuildValue("i", result);
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	pStorageServer = NULL;
	*group_name = '\0';

	int upload_type;
	char *prefix_name;
	const char *file_ext_name;
	char slave_filename[256];
	int slave_filename_len;

	if (upload_typestr == NULL) {
		upload_type = FDFS_UPLOAD_BY_FILE;
	} else if (strcmp(upload_typestr, "BUFF") == 0) {
		upload_type = FDFS_UPLOAD_BY_BUFF;
	} else if (strcmp(upload_typestr, "CALLBACK") == 0) {
		upload_type = FDFS_UPLOAD_BY_CALLBACK;
	} else {
		upload_type = FDFS_UPLOAD_BY_FILE;
	}

	store_path_index = 0;

	{
		ConnectionInfo
		    storageServers[FDFS_MAX_SERVERS_EACH_GROUP];
		ConnectionInfo *pServer;
		ConnectionInfo *pServerEnd;
		int storage_count;

		if ((result =
		     tracker_query_storage_store_list_without_group
		     (pTrackerServer, storageServers,
		      FDFS_MAX_SERVERS_EACH_GROUP, &storage_count,
		      group_name, &store_path_index)) == 0) {
			printf
			    ("tracker_query_storage_store_list_without_group: \n");
			pServerEnd =
			    storageServers + storage_count;
			for (pServer = storageServers;
			     pServer < pServerEnd; pServer++) {
				printf
				    ("\tserver %d. group_name=%s, "
				     "ip_addr=%s, port=%d\n",
				     (int) (pServer -
					    storageServers) + 1,
				     group_name, pServer->ip_addr,
				     pServer->port);
			}
			printf("\n");
		}
	}

	if ((result = tracker_query_storage_store(pTrackerServer,
						  &storageServer,
						  group_name,
						  &store_path_index))
	    != 0) {
		fdfs_client_destroy();
		printf("tracker_query_storage fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	printf("group_name=%s, ip_addr=%s, port=%d\n",
	       group_name, storageServer.ip_addr,
	       storageServer.port);

	if ((pStorageServer =
	     tracker_connect_server(&storageServer,
				    &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	memset(&meta_list, 0, sizeof(meta_list));
	meta_count = 0;
	strcpy(meta_list[meta_count].name, "ext_name");
	strcpy(meta_list[meta_count].value, "jpg");
	meta_count++;
	strcpy(meta_list[meta_count].name, "width");
	strcpy(meta_list[meta_count].value, "160");
	meta_count++;
	strcpy(meta_list[meta_count].name, "height");
	strcpy(meta_list[meta_count].value, "80");
	meta_count++;
	strcpy(meta_list[meta_count].name, "file_size");
	strcpy(meta_list[meta_count].value, "115120");
	meta_count++;

	file_ext_name = fdfs_get_file_ext_name(local_filename);
	*group_name = '\0';

	if (upload_type == FDFS_UPLOAD_BY_FILE) {
		result = storage_upload_by_filename(pTrackerServer,
						    pStorageServer,
						    store_path_index,
						    local_filename,
						    file_ext_name,
						    meta_list,
						    meta_count,
						    group_name,
						    remote_filename);

		printf("storage_upload_by_filename\n");
	} else if (upload_type == FDFS_UPLOAD_BY_BUFF) {
		char *file_content;
		if ((result = getFileContent(local_filename,
					     &file_content,
					     &file_size)) == 0) {
			result =
			    storage_upload_by_filebuff
			    (pTrackerServer, pStorageServer,
			     store_path_index, file_content,
			     file_size, file_ext_name, meta_list,
			     meta_count, group_name,
			     remote_filename);
			free(file_content);
		}

		printf("storage_upload_by_filebuff\n");
	} else {
		struct stat stat_buf;

		if (stat(local_filename, &stat_buf) == 0 &&
		    S_ISREG(stat_buf.st_mode)) {
			file_size = stat_buf.st_size;
			result =
			    storage_upload_by_callback
			    (pTrackerServer, pStorageServer,
			     store_path_index, uploadFileCallback,
			     local_filename, file_size,
			     file_ext_name, meta_list, meta_count,
			     group_name, remote_filename);
		}

		printf("storage_upload_by_callback\n");
	}

	if (result != 0) {
		printf("upload file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
		tracker_disconnect_server_ex(pStorageServer, true);
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	if (g_tracker_server_http_port == 80) {
		*szPortPart = '\0';
	} else {
		sprintf(szPortPart, ":%d",
			g_tracker_server_http_port);
	}

	sprintf(file_id, "%s/%s", group_name, remote_filename);
	url_len = sprintf(file_url, "http://%s%s/%s",
			  pStorageServer->ip_addr, szPortPart,
			  file_id);
	if (g_anti_steal_token) {
		ts = time(NULL);
		fdfs_http_gen_token(&g_anti_steal_secret_key,
				    file_id, ts, token);
		sprintf(file_url + url_len, "?token=%s&ts=%d",
			token, (int) ts);
	}

	printf("group_name=%s, remote_filename=%s\n",
	       group_name, remote_filename);

	fdfs_get_file_info(group_name, remote_filename,
			   &file_info);
	printf("source ip address: %s\n",
	       file_info.source_ip_addr);
	printf("file timestamp=%s\n",
	       formatDatetime(file_info.create_timestamp,
			      "%Y-%m-%d %H:%M:%S", szDatetime,
			      sizeof(szDatetime)));
	printf("file size=%" PRId64 "\n", file_info.file_size);
	printf("file crc32=%u\n", file_info.crc32);
	printf("example file url: %s\n", file_url);

	strcpy(master_filename, remote_filename);
	*remote_filename = '\0';
	if (upload_type == FDFS_UPLOAD_BY_FILE) {
		prefix_name = "_big";
		result =
		    storage_upload_slave_by_filename
		    (pTrackerServer, NULL, local_filename,
		     master_filename, prefix_name, file_ext_name,
		     meta_list, meta_count, group_name,
		     remote_filename);

		printf("storage_upload_slave_by_filename\n");
	} else if (upload_type == FDFS_UPLOAD_BY_BUFF) {
		char *file_content;
		prefix_name = "1024x1024";
		if ((result = getFileContent(local_filename,
					     &file_content,
					     &file_size)) == 0) {
			result =
			    storage_upload_slave_by_filebuff
			    (pTrackerServer, NULL, file_content,
			     file_size, master_filename,
			     prefix_name, file_ext_name, meta_list,
			     meta_count, group_name,
			     remote_filename);
			free(file_content);
		}

		printf("storage_upload_slave_by_filebuff\n");
	} else {
		struct stat stat_buf;

		prefix_name = "-small";
		if (stat(local_filename, &stat_buf) == 0 &&
		    S_ISREG(stat_buf.st_mode)) {
			file_size = stat_buf.st_size;
			result =
			    storage_upload_slave_by_callback
			    (pTrackerServer, NULL,
			     uploadFileCallback, local_filename,
			     file_size, master_filename,
			     prefix_name, file_ext_name, meta_list,
			     meta_count, group_name,
			     remote_filename);
		}

		printf("storage_upload_slave_by_callback\n");
	}

	if (result != 0) {
		printf("upload slave file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
		tracker_disconnect_server_ex(pStorageServer, true);
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	if (g_tracker_server_http_port == 80) {
		*szPortPart = '\0';
	} else {
		sprintf(szPortPart, ":%d",
			g_tracker_server_http_port);
	}

	sprintf(file_id, "%s/%s", group_name, remote_filename);
	url_len = sprintf(file_url, "http://%s%s/%s",
			  pStorageServer->ip_addr, szPortPart,
			  file_id);
	if (g_anti_steal_token) {
		ts = time(NULL);
		fdfs_http_gen_token(&g_anti_steal_secret_key,
				    file_id, ts, token);
		sprintf(file_url + url_len, "?token=%s&ts=%d",
			token, (int) ts);
	}

	printf("group_name=%s, remote_filename=%s\n",
	       group_name, remote_filename);

	fdfs_get_file_info(group_name, remote_filename,
			   &file_info);

	printf("source ip address: %s\n",
	       file_info.source_ip_addr);
	printf("file timestamp=%s\n",
	       formatDatetime(file_info.create_timestamp,
			      "%Y-%m-%d %H:%M:%S", szDatetime,
			      sizeof(szDatetime)));
	printf("file size=%" PRId64 "\n", file_info.file_size);
	printf("file crc32=%u\n", file_info.crc32);
	printf("example file url: %s\n", file_url);

	if (fdfs_gen_slave_filename(master_filename,
				    prefix_name, file_ext_name,
				    slave_filename,
				    &slave_filename_len) == 0) {

		if (strcmp(remote_filename, slave_filename) != 0) {
			printf("slave_filename=%s\n"
			       "remote_filename=%s\n"
			       "not equal!\n",
			       slave_filename, remote_filename);
		}
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	fdfs_client_destroy();

    return Py_BuildValue("(i, s)", result, remote_filename);
}

static PyObject *fdfs_download(PyObject *self, PyObject *args)
{
	char *conf_filename;
	char *local_filename;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;
	char *file_buff;
	int64_t file_size;

	if (!PyArg_ParseTuple(args, "sssz",  &conf_filename, &group_name, &remote_filename, &local_filename))
		return NULL;

	printf("conf_filename: %s, group_name: %s, remote_filename: %s, local_filename: %s\n", conf_filename, group_name, remote_filename, local_filename);

	if ((result = fdfs_init(conf_filename)) != 0) {
		return Py_BuildValue("i", result);
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	pStorageServer = NULL;
	if ((result =
    	tracker_query_storage_fetch(pTrackerServer,
					&storageServer,
					group_name,
					remote_filename)) != 0) {
		fdfs_client_destroy();
		printf("tracker_query_storage_fetch fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	printf("storage=%s:%d\n", storageServer.ip_addr,
	       storageServer.port);

	if ((pStorageServer =
	     tracker_connect_server(&storageServer,
				    &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	if (local_filename != NULL) {
		if (strcmp(local_filename, "CALLBACK") ==
		    0) {
			FILE *fp;
			fp = fopen(local_filename, "wb");
			if (fp == NULL) {
				result =
				    errno !=
				    0 ? errno : EPERM;
				printf
				    ("open file \"%s\" fail, "
				     "errno: %d, error info: %s",
				     local_filename,
				     result,
				     STRERROR(result));
			} else {
				result =
				    storage_download_file_ex
				    (pTrackerServer,
				     pStorageServer,
				     group_name,
				     remote_filename, 0, 0,
				     writeToFileCallback,
				     fp, &file_size);
				fclose(fp);
			}
		} else {
			result =
			    storage_download_file_to_file
			    (pTrackerServer,
			     pStorageServer, group_name,
			     remote_filename,
			     local_filename, &file_size);
		}
	} else {
		file_buff = NULL;
		if ((result =
		     storage_download_file_to_buff
		     (pTrackerServer, pStorageServer,
		      group_name, remote_filename,
		      &file_buff, &file_size)) == 0) {
			local_filename =
			    strrchr(remote_filename, '/');
			if (local_filename != NULL) {
				local_filename++;	//skip /
			} else {
				local_filename =
				    remote_filename;
			}

			result =
			    writeToFile(local_filename,
					file_buff,
					file_size);

			free(file_buff);
		}
	}

	if (result == 0) {
		printf("download file success, "
		       "file size=%" PRId64
		       ", file save to %s\n", file_size,
		       local_filename);
	} else {
		printf("download file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}
	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	fdfs_client_destroy();

	return Py_BuildValue("i", result);
}


static PyObject *fdfs_delete(PyObject *self, PyObject *args)
{
	char *conf_filename;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;

	if (!PyArg_ParseTuple(args, "sss",  &conf_filename, &group_name, &remote_filename))
		return NULL;

	if ((result = fdfs_init(conf_filename)) != 0) {
		return Py_BuildValue("i", result);
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	pStorageServer = NULL;

	result =
	    tracker_query_storage_update(pTrackerServer,
					 &storageServer,
					 group_name,
					 remote_filename);
	if ((result =
	    tracker_query_storage_fetch(pTrackerServer,
					&storageServer,
					group_name,
					remote_filename)) != 0) {
		fdfs_client_destroy();
		printf("tracker_query_storage_fetch fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}
	if ((pStorageServer =
	     tracker_connect_server(&storageServer,
				    &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}
	if ((result = storage_delete_file(pTrackerServer,
					  NULL, group_name,
					  remote_filename))
	    == 0) {
		printf("delete file success\n");
	} else {
		printf("delete file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	fdfs_client_destroy();

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_getmeta(PyObject *self, PyObject *args)
{
	char *conf_filename;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;
	int meta_count;
	int i;
	FDFSMetaData *pMetaList;

	if (!PyArg_ParseTuple(args, "sss",  &conf_filename, &group_name, &remote_filename))
		return NULL;

	log_init();
	g_log_context.log_level = LOG_DEBUG;

	if ((result = fdfs_client_init(conf_filename)) != 0) {
		return Py_BuildValue("i", result);
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	pStorageServer = NULL;
	result =
	    tracker_query_storage_fetch(pTrackerServer,
					&storageServer,
					group_name,
					remote_filename);

	if (result != 0) {
		fdfs_client_destroy();
		printf("tracker_query_storage_fetch fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	printf("storage=%s:%d\n", storageServer.ip_addr,
	       storageServer.port);

	if ((pStorageServer =
	     tracker_connect_server(&storageServer,
				    &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}
	if ((result = storage_get_metadata(pTrackerServer,
					   pStorageServer,
					   group_name,
					   remote_filename,
					   &pMetaList,
					   &meta_count)) ==
	    0) {
		printf("get meta data success, "
		       "meta count=%d\n", meta_count);
		for (i = 0; i < meta_count; i++) {
			printf("%s=%s\n",
			       pMetaList[i].name,
			       pMetaList[i].value);
		}

		free(pMetaList);
	} else {
		printf("getmeta fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	fdfs_client_destroy();

	return Py_BuildValue("i", result);
}
// 方法列表
static PyMethodDef FDFSMethods[] = {

	//python中注册的函数名
	{ "fdfs_upload", fdfs_upload, METH_VARARGS, "Execute a shell command." },
	{ "fdfs_download", fdfs_download, METH_VARARGS, "Execute a shell command." },
	{ "fdfs_delete", fdfs_delete, METH_VARARGS, "Execute a shell command." },
	{ "fdfs_getmeta", fdfs_getmeta, METH_VARARGS, "Execute a shell command." },
	{ NULL, NULL, 0, NULL }
};

// 模块初始化方法  
PyMODINIT_FUNC initfdfsclient() {

	//初始模块
	PyObject *m = Py_InitModule("fdfsclient", FDFSMethods);
	if (m == NULL)
		return;
}

static int fdfs_init(const char *conf_filename)
{
	int result;

	log_init();
	g_log_context.log_level = LOG_DEBUG;

	return result = fdfs_client_init(conf_filename);
}

static int writeToFileCallback(void *arg, const int64_t file_size,
			const char *data, const int current_size)
{
	if (arg == NULL) {
		return EINVAL;
	}

	if (fwrite(data, current_size, 1, (FILE *) arg) != 1) {
		return errno != 0 ? errno : EIO;
	}

	return 0;
}

static int uploadFileCallback(void *arg, const int64_t file_size, int sock)
{
	int64_t total_send_bytes;
	char *filename;

	if (arg == NULL) {
		return EINVAL;
	}

	filename = (char *) arg;
	return tcpsendfile(sock, filename, file_size,
			   g_fdfs_network_timeout, &total_send_bytes);
}
