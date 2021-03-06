/*================================================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename:fastdfs.c
 *   author:sulit sulitsrc@163.com
 *   modify date,time:2015-05-21 15:27
 *   discription:
 *
 *================================================================*/
#include <Python.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fdfs_client.h"
#include "fdfs_global.h"
#include "base64.h"
#include "sockopt.h"
#include "logger.h"
#include "fdfs_http_shared.h"

#define FDFSPYMOD "fdfspyclient"

static int writeToFileCallback(void *arg, const int64_t file_size,
			       const char *data, const int current_size);
static int uploadFileCallback(void *arg, const int64_t file_size,
			      int sock);
static int list_storages(ConnectionInfo * pTrackerServer,
			 FDFSGroupStat * pGroupStat);
static int list_all_groups(ConnectionInfo * pTrackerServer,
			   const char *group_name);

static PyObject *fdfs_init(PyObject * self, PyObject * args)
{
	int result;
	char *conf_filename;
	if (!PyArg_ParseTuple(args, "s", &conf_filename)) {
		printf("usage: " FDFSPYMOD ".fdfs_init(conf_filename)\n");
		return NULL;
	}

	log_init();
	g_log_context.log_level = LOG_DEBUG;

	result = fdfs_client_init(conf_filename);

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_upload(PyObject * self, PyObject * args)
{
	char *local_filename;
	char *upload_typestr;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	char remote_filename[256];
	FDFSMetaData meta_list[32];
	int meta_count;
	char token[32 + 1];
	char file_id[128];
	char file_url[256];
	char szPortPart[16];
	int url_len;
	time_t ts;
	int64_t file_size;
	int store_path_index;

	if (!PyArg_ParseTuple
	    (args, "sz", &local_filename, &upload_typestr)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_upload(local_filename, upload_typestr | None)\n");
		fdfs_client_destroy();
		return NULL;
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
	const char *file_ext_name;

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
		ConnectionInfo storageServers[FDFS_MAX_SERVERS_EACH_GROUP];
		int storage_count;

		tracker_query_storage_store_list_without_group
		    (pTrackerServer, storageServers,
		     FDFS_MAX_SERVERS_EACH_GROUP, &storage_count,
		     group_name, &store_path_index);
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

	if ((pStorageServer =
	     tracker_connect_server(&storageServer, &result)) == NULL) {
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
			     meta_count, group_name, remote_filename);
			free(file_content);
		}

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
		sprintf(szPortPart, ":%d", g_tracker_server_http_port);
	}

	sprintf(file_id, "%s/%s", group_name, remote_filename);
	url_len = sprintf(file_url, "http://%s%s/%s",
			  pStorageServer->ip_addr, szPortPart, file_id);
	if (g_anti_steal_token) {
		ts = time(NULL);
		fdfs_http_gen_token(&g_anti_steal_secret_key,
				    file_id, ts, token);
		sprintf(file_url + url_len, "?token=%s&ts=%d",
			token, (int) ts);
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("(i, s, s, s)", result, group_name,
			     remote_filename, file_url);
}

static PyObject *fdfs_download(PyObject * self, PyObject * args)
{
	char *local_filename;
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;
	char *file_buff;
	int64_t file_size;
	char filesizebuff[1024];

	if (!PyArg_ParseTuple
	    (args, "ssz", &group_name, &remote_filename,
	     &local_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_download(group_name, remote_filename, local_filename | None)\n");
		fdfs_client_destroy();

		return NULL;
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

	if ((pStorageServer =
	     tracker_connect_server(&storageServer, &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	if (local_filename != NULL) {
		if (strcmp(local_filename, "CALLBACK") == 0) {
			FILE *fp;
			fp = fopen(local_filename, "wb");
			if (fp == NULL) {
				result = errno != 0 ? errno : EPERM;
				printf
				    ("open file \"%s\" fail, "
				     "errno: %d, error info: %s",
				     local_filename,
				     result, STRERROR(result));
			} else {
				result =
				    storage_download_file_ex
				    (pTrackerServer,
				     pStorageServer,
				     group_name,
				     remote_filename, 0, 0,
				     writeToFileCallback, fp, &file_size);
				fclose(fp);
			}
		} else {
			result =
			    storage_download_file_to_file
			    (pTrackerServer,
			     pStorageServer, group_name,
			     remote_filename, local_filename, &file_size);
		}
	} else {
		file_buff = NULL;
		if ((result =
		     storage_download_file_to_buff
		     (pTrackerServer, pStorageServer,
		      group_name, remote_filename,
		      &file_buff, &file_size)) == 0) {
			local_filename = strrchr(remote_filename, '/');
			if (local_filename != NULL) {
				local_filename++;	//skip /
			} else {
				local_filename = remote_filename;
			}

			result =
			    writeToFile(local_filename,
					file_buff, file_size);

			free(file_buff);
		}
	}

	if (result == 0) {
		snprintf(filesizebuff, sizeof(filesizebuff), "%" PRId64,
			 file_size);
	} else {
		printf("download file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}
	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("(i, s, s)", result, local_filename,
			     filesizebuff);
}

static PyObject *fdfs_delete(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;

	if (!PyArg_ParseTuple(args, "ss", &group_name, &remote_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_delete(group_name, remote_filename)\n");
		fdfs_client_destroy();

		return NULL;
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
					 group_name, remote_filename);
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
	     tracker_connect_server(&storageServer, &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}
	if ((result = storage_delete_file(pTrackerServer,
					  NULL, group_name,
					  remote_filename))
	    == 0) {
	} else {
		printf("delete file fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_getmeta(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;
	int meta_count;
	int i;
	FDFSMetaData *pMetaList;
	PyObject *metatable = NULL;
	char kv[1024];

	if (!PyArg_ParseTuple(args, "ss", &group_name, &remote_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_getmeta(group_name, remote_filename)\n");
		fdfs_client_destroy();

		return NULL;
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
					group_name, remote_filename);

	if (result != 0) {
		fdfs_client_destroy();
		printf("tracker_query_storage_fetch fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	if ((pStorageServer =
	     tracker_connect_server(&storageServer, &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}
	if ((result = storage_get_metadata(pTrackerServer,
					   pStorageServer,
					   group_name,
					   remote_filename,
					   &pMetaList,
					   &meta_count)) == 0) {
		metatable = PyTuple_New(meta_count);
		for (i = 0; i < meta_count; i++) {
			snprintf(kv, sizeof(kv), "%s=%s",
				 pMetaList[i].name, pMetaList[i].value);
			PyTuple_SetItem(metatable, i,
					PyString_FromString(kv));
		}

		free(pMetaList);
	} else {
		printf("getmeta fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("iiO", result, meta_count, metatable);
}

static PyObject *fdfs_setmeta(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	ConnectionInfo *pStorageServer;
	int result;
	ConnectionInfo storageServer;
	char *group_name;
	char *remote_filename;
	int meta_count;
	FDFSMetaData *pMetaList;
	char *meta_buff;
	char *op_flag;

	if (!PyArg_ParseTuple
	    (args, "ssss", &group_name, &remote_filename, &op_flag,
	     &meta_buff)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_setmeta(group_name, remote_filename,"
		       " op_flag, metadata_list)\n"
		       "\top_flag: %c for overwrite, " "%c for merge\n"
		       "\tmetadata_list: name1=value1,"
		       "name2=value2,...\n",
		       STORAGE_SET_METADATA_FLAG_OVERWRITE,
		       STORAGE_SET_METADATA_FLAG_MERGE);

		fdfs_client_destroy();
		return NULL;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	pStorageServer = NULL;
	if ((result = tracker_query_storage_update(pTrackerServer,
						   &storageServer,
						   group_name,
						   remote_filename)) !=
	    0) {

		fdfs_client_destroy();
		printf("tracker_query_storage_fetch fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	if ((pStorageServer =
	     tracker_connect_server(&storageServer, &result)) == NULL) {
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}
	pMetaList = fdfs_split_metadata_ex(meta_buff,
					   ',', '=', &meta_count, &result);
	if (pMetaList == NULL) {
		printf("Out of memory!\n");
		return Py_BuildValue("i", ENOMEM);
	}

	if ((result = storage_set_metadata(pTrackerServer,
					   NULL,
					   group_name,
					   remote_filename,
					   pMetaList,
					   meta_count, *op_flag)) == 0) {
	} else {
		printf("setmeta fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	}

	free(pMetaList);

	tracker_disconnect_server_ex(pStorageServer, true);
	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_query_servers(PyObject * self, PyObject * args)
{
	int result;
	char *group_name;
	char *remote_filename;
	ConnectionInfo *pTrackerServer;
	int i;
	ConnectionInfo storageServers[FDFS_MAX_SERVERS_EACH_GROUP];
	int server_count;
	char ip_port[80];
	PyObject *storageServertable = NULL;

	if (!PyArg_ParseTuple(args, "ss", &group_name, &remote_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_query_servers(group_name, remote_filename)\n");
		fdfs_client_destroy();
		return NULL;
	}
	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	result = tracker_query_storage_list(pTrackerServer,
					    storageServers,
					    FDFS_MAX_SERVERS_EACH_GROUP,
					    &server_count,
					    group_name, remote_filename);

	if (result != 0) {
		printf("tracker_query_storage_list fail, "
		       "group_name=%s, filename=%s, "
		       "error no: %d, error info: %s\n",
		       group_name, remote_filename,
		       result, STRERROR(result));
	} else {
		storageServertable = PyTuple_New(server_count);
		for (i = 0; i < server_count; i++) {
			snprintf(ip_port, sizeof(ip_port),
				 "ip:%s, port:%d",
				 storageServers[i].ip_addr,
				 storageServers[i].port);
			PyTuple_SetItem(storageServertable, i,
					PyString_FromString(ip_port));
		}
	}

	tracker_disconnect_server_ex(pTrackerServer, result != 0);

	return Py_BuildValue("iiO", result, server_count,
			     storageServertable);
}

static PyObject *fdfs_append_file(PyObject * self, PyObject * args)
{
	char *local_filename;
	ConnectionInfo *pTrackerServer;
	int result;
	char *appender_file_id;

	if (!PyArg_ParseTuple
	    (args, "ss", &appender_file_id, &local_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_append_file(append_file_id, local_filename)\n"
		       "\tappend_file_id:groupname+remote_filename(ex:group1/M00/00/00/wKj_gVVjzBOAMy5EAAAD6VEwZK86469523)\n");
		fdfs_client_destroy();
		return NULL;
	}
	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	if ((result = storage_append_by_filename1(pTrackerServer,
						  NULL, local_filename,
						  appender_file_id)) !=
	    0) {
		printf("append file fail, "
		       "error no: %d, error info: %s\n", result,
		       STRERROR(result));
		return Py_BuildValue("i", result);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_file_info(PyObject * self, PyObject * args)
{
	char *file_id;
	int result;
	FDFSFileInfo file_info;
	PyObject *fileinfotable = NULL;
	char buff[1024];

	if (!PyArg_ParseTuple(args, "s", &file_id)) {
		printf("usage: " FDFSPYMOD ".fdfs_file_info(file_id)\n"
		       "\tappend_file_id:groupname+remote_filename(ex:group1/M00/00/00/wKj_gVVjzBOAMy5EAAAD6VEwZK86469523)\n");
		fdfs_client_destroy();
		return NULL;
	}

	ignore_signal_pipe();

	memset(&file_info, 0, sizeof(file_info));
	result = fdfs_get_file_info_ex1(file_id, true, &file_info);
	if (result != 0) {
		printf("query file info fail, "
		       "error no: %d, error info: %s\n",
		       result, STRERROR(result));
	} else {
		char szDatetime[32];

		fileinfotable = PyTuple_New(5);
		snprintf(buff, sizeof(buff), "source storageid: %d",
			 file_info.source_id);
		PyTuple_SetItem(fileinfotable, 0,
				PyString_FromString(buff));
		snprintf(buff, sizeof(buff), "source ip address: %s",
			 file_info.source_ip_addr);
		PyTuple_SetItem(fileinfotable, 1,
				PyString_FromString(buff));
		snprintf(buff, sizeof(buff), "file create timestamp: %s",
			 formatDatetime(file_info.create_timestamp,
					"%Y-%m-%d %H:%M:%S", szDatetime,
					sizeof(szDatetime)));
		PyTuple_SetItem(fileinfotable, 2,
				PyString_FromString(buff));
		snprintf(buff, sizeof(buff), "file size: %" PRId64 "",
			 file_info.file_size);
		PyTuple_SetItem(fileinfotable, 3,
				PyString_FromString(buff));
		snprintf(buff, sizeof(buff), "file crc32: %u (0x%08X)",
			 file_info.crc32, file_info.crc32);
		PyTuple_SetItem(fileinfotable, 4,
				PyString_FromString(buff));
	}

	tracker_close_all_connections();

	return Py_BuildValue("iO", result, fileinfotable);
}

static PyObject *fdfs_upload_append(PyObject * self, PyObject * args)
{
	char *local_filename;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	char file_id[128];

	if (!PyArg_ParseTuple(args, "s", &local_filename)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_upload_append(local_filename)\n");
		fdfs_client_destroy();
		return NULL;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	store_path_index = 0;
	if ((result = tracker_query_storage_store(pTrackerServer,
						  &storageServer,
						  group_name,
						  &store_path_index)) !=
	    0) {
		fdfs_client_destroy();
		fprintf(stderr, "tracker_query_storage fail, "
			"error no: %d, error info: %s\n",
			result, STRERROR(result));
		return Py_BuildValue("i", result);
	}

	result = storage_upload_appender_by_filename1(pTrackerServer,
						      &storageServer,
						      store_path_index,
						      local_filename, NULL,
						      NULL, 0, group_name,
						      file_id);
	if (result != 0) {
		fprintf(stderr, "upload file fail, "
			"error no: %d, error info: %s\n",
			result, STRERROR(result));

		tracker_disconnect_server_ex(pTrackerServer, true);
		fdfs_client_destroy();
		return Py_BuildValue("i", result);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("(i, s)", result, file_id);
}

static PyObject *fdfs_list_all_groups(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	int result;
	char *tracker_server;
	char *group_name;

	if (!PyArg_ParseTuple(args, "zz", &tracker_server, &group_name)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_list_all_groups(tracker_server | None, group_name | None)\n");
		fdfs_client_destroy();
		return NULL;
	}

	if (tracker_server == NULL) {
		if (g_tracker_group.server_count > 1) {
			srand(time(NULL));
			rand();	//discard the first
			g_tracker_group.server_index =
			    (int) ((g_tracker_group.server_count *
				    (double) rand())
				   / (double)
				   RAND_MAX);
		}
	} else {
		int i;
		char ip_addr[IP_ADDRESS_SIZE];

		*ip_addr = '\0';
		if (getIpaddrByName
		    (tracker_server, ip_addr, sizeof(ip_addr))
		    == INADDR_NONE) {
			printf("resolve ip address of tracker server: %s "
			       "fail!\n", tracker_server);
			return Py_BuildValue("i", 2);
		}

		for (i = 0; i < g_tracker_group.server_count; i++) {
			if (strcmp(g_tracker_group.servers[i].ip_addr,
				   ip_addr) == 0) {
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count) {
			printf("tracker server: %s not exists!\n",
			       tracker_server);
			return Py_BuildValue("i", 2);
		}
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	if (group_name == NULL) {
		result = list_all_groups(pTrackerServer, NULL);
	} else {
		result = list_all_groups(pTrackerServer, group_name);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);

	return Py_BuildValue("i", result);
}

static PyObject *fdfs_delete_group(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	int result;
	char *tracker_server;
	char *group_name;

	if (!PyArg_ParseTuple(args, "zs", &tracker_server, &group_name)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_delete_group(tracker_server | None, group_name)\n");
		fdfs_client_destroy();
		return NULL;
	}

	if (tracker_server == NULL) {
		if (g_tracker_group.server_count > 1) {
			srand(time(NULL));
			rand();	//discard the first
			g_tracker_group.server_index =
			    (int) ((g_tracker_group.server_count *
				    (double) rand())
				   / (double)
				   RAND_MAX);
		}
	} else {
		int i;
		char ip_addr[IP_ADDRESS_SIZE];

		*ip_addr = '\0';
		if (getIpaddrByName
		    (tracker_server, ip_addr, sizeof(ip_addr))
		    == INADDR_NONE) {
			printf("resolve ip address of tracker server: %s "
			       "fail!\n", tracker_server);
			return Py_BuildValue("i", 2);
		}

		for (i = 0; i < g_tracker_group.server_count; i++) {
			if (strcmp(g_tracker_group.servers[i].ip_addr,
				   ip_addr) == 0) {
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count) {
			printf("tracker server: %s not exists!\n",
			       tracker_server);
			return Py_BuildValue("i", 2);
		}
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	if ((result =
	     tracker_delete_group(&g_tracker_group, group_name)) != 0) {
		printf("delete group: %s fail, "
		       "error no: %d, error info: %s\n",
		       group_name, result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	return Py_BuildValue("i", result);
}

static PyObject *fdfs_delete_server(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	int result;
	char *tracker_server;
	char *storage_id;
	char *group_name;

	if (!PyArg_ParseTuple
	    (args, "zss", &tracker_server, &group_name, &storage_id)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_delete_server(tracker_server | None, group_name, storage_id)\n");
		fdfs_client_destroy();
		return NULL;
	}

	if (tracker_server == NULL) {
		if (g_tracker_group.server_count > 1) {
			srand(time(NULL));
			rand();	//discard the first
			g_tracker_group.server_index =
			    (int) ((g_tracker_group.server_count *
				    (double) rand())
				   / (double)
				   RAND_MAX);
		}
	} else {
		int i;
		char ip_addr[IP_ADDRESS_SIZE];

		*ip_addr = '\0';
		if (getIpaddrByName
		    (tracker_server, ip_addr, sizeof(ip_addr))
		    == INADDR_NONE) {
			printf("resolve ip address of tracker server: %s "
			       "fail!\n", tracker_server);
			return Py_BuildValue("i", 2);
		}

		for (i = 0; i < g_tracker_group.server_count; i++) {
			if (strcmp(g_tracker_group.servers[i].ip_addr,
				   ip_addr) == 0) {
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count) {
			printf("tracker server: %s not exists!\n",
			       tracker_server);
			return Py_BuildValue("i", 2);
		}
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	if ((result =
	     tracker_delete_storage(&g_tracker_group,
				    group_name, storage_id)) != 0) {
		printf
		    ("delete storage server %s::%s fail, "
		     "error no: %d, error info: %s\n",
		     group_name, storage_id, result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	return Py_BuildValue("i", result);
}

static PyObject *fdfs_set_trunk_server(PyObject * self, PyObject * args)
{
	ConnectionInfo *pTrackerServer;
	int result;
	char *tracker_server;
	char *group_name;
	char *storage_id;
	char new_trunk_server_id[FDFS_STORAGE_ID_MAX_SIZE];

	if (!PyArg_ParseTuple
	    (args, "zss", &tracker_server, &group_name, &storage_id)) {
		printf("usage: " FDFSPYMOD
		       ".fdfs_set_trunk_server(tracker_server | None, group_name, storage_id)\n");
		fdfs_client_destroy();
		return NULL;
	}

	if (tracker_server == NULL) {
		if (g_tracker_group.server_count > 1) {
			srand(time(NULL));
			rand();	//discard the first
			g_tracker_group.server_index =
			    (int) ((g_tracker_group.server_count *
				    (double) rand())
				   / (double)
				   RAND_MAX);
		}
	} else {
		int i;
		char ip_addr[IP_ADDRESS_SIZE];

		*ip_addr = '\0';
		if (getIpaddrByName
		    (tracker_server, ip_addr, sizeof(ip_addr))
		    == INADDR_NONE) {
			printf("resolve ip address of tracker server: %s "
			       "fail!\n", tracker_server);
			return Py_BuildValue("i", 2);
		}

		for (i = 0; i < g_tracker_group.server_count; i++) {
			if (strcmp(g_tracker_group.servers[i].ip_addr,
				   ip_addr) == 0) {
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count) {
			printf("tracker server: %s not exists!\n",
			       tracker_server);
			return Py_BuildValue("i", 2);
		}
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL) {
		fdfs_client_destroy();
		result = errno != 0 ? errno : ECONNREFUSED;
		return Py_BuildValue("i", result);
	}

	if ((result = tracker_set_trunk_server(&g_tracker_group,
					       group_name,
					       storage_id,
					       new_trunk_server_id))
	    != 0) {
		printf("set trunk server %s::%s fail, "
		       "error no: %d, error info: %s\n",
		       group_name, storage_id, result, STRERROR(result));
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	return Py_BuildValue("(i, s)", result, new_trunk_server_id);
}

static PyObject *fdfs_destroy(PyObject * self)
{
	fdfs_client_destroy();
	return Py_BuildValue("s", "client exited");
}

// 方法列表
static PyMethodDef FDFSMethods[] = {

	//python中注册的函数名
	{"fdfs_init", fdfs_init, METH_VARARGS,
	 "fdfsclient init."},
	{"fdfs_upload", fdfs_upload, METH_VARARGS,
	 "fdfsclient upload."},
	{"fdfs_download", fdfs_download, METH_VARARGS,
	 "fdfsclient download."},
	{"fdfs_delete", fdfs_delete, METH_VARARGS,
	 "fdfsclient delete."},
	{"fdfs_getmeta", fdfs_getmeta, METH_VARARGS,
	 "fdfsclient getmeta."},
	{"fdfs_setmeta", fdfs_setmeta, METH_VARARGS,
	 "fdfsclient setmeta."},
	{"fdfs_query_servers", fdfs_query_servers, METH_VARARGS,
	 "fdfsclient query servers."},
	{"fdfs_upload_append", fdfs_upload_append, METH_VARARGS,
	 "fdfsclient upload append."},
	{"fdfs_append_file", fdfs_append_file, METH_VARARGS,
	 "fdfsclient append file."},
	{"fdfs_file_info", fdfs_file_info, METH_VARARGS,
	 "fdfsclient file info."},
	{"fdfs_list_all_groups", fdfs_list_all_groups, METH_VARARGS,
	 "fdfsclient list all groups or one group."},
	//{"fdfs_list_storages",  fdfs_list_storages, METH_VARARGS,
	// "fdfsclient list storages."},
	{"fdfs_delete_group", fdfs_delete_group, METH_VARARGS,
	 "fdfsclient delete one group."},
	{"fdfs_delete_server", fdfs_delete_server, METH_VARARGS,
	 "fdfsclient delete one storages server."},
	{"fdfs_set_trunk_server", fdfs_set_trunk_server, METH_VARARGS,
	 "fdfsclient set trunk server."},
	{"fdfs_destroy", (PyCFunction) fdfs_destroy, METH_NOARGS,
	 "fdfsclient destroy."},
	{NULL, NULL, 0, NULL}
};

// 模块初始化方法
PyMODINIT_FUNC initfdfspyclient()
{

	//初始模块
	PyObject *m = Py_InitModule("fdfspyclient", FDFSMethods);
	if (m == NULL)
		return;
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

static int list_storages(ConnectionInfo * pTrackerServer,
			 FDFSGroupStat * pGroupStat)
{
	int result;
	int storage_count;
	FDFSStorageInfo storage_infos[FDFS_MAX_SERVERS_EACH_GROUP];
	FDFSStorageInfo *p;
	FDFSStorageInfo *pStorage;
	FDFSStorageInfo *pStorageEnd;
	FDFSStorageStat *pStorageStat;
	char szJoinTime[32];
	char szUpTime[32];
	char szLastHeartBeatTime[32];
	char szSrcUpdTime[32];
	char szSyncUpdTime[32];
	char szSyncedTimestamp[32];
	char szSyncedDelaySeconds[128];
	char szHostname[128];
	char szHostnamePrompt[128 + 8];
	int k;
	int max_last_source_update;

	printf("group name = %s\n"
	       "disk total space = %" PRId64 " MB\n"
	       "disk free space = %" PRId64 " MB\n"
	       "trunk free space = %" PRId64 " MB\n"
	       "storage server count = %d\n"
	       "active server count = %d\n"
	       "storage server port = %d\n"
	       "storage HTTP port = %d\n"
	       "store path count = %d\n"
	       "subdir count per path = %d\n"
	       "current write server index = %d\n"
	       "current trunk file id = %d\n\n",
	       pGroupStat->group_name,
	       pGroupStat->total_mb,
	       pGroupStat->free_mb,
	       pGroupStat->trunk_free_mb,
	       pGroupStat->count,
	       pGroupStat->active_count,
	       pGroupStat->storage_port,
	       pGroupStat->storage_http_port,
	       pGroupStat->store_path_count,
	       pGroupStat->subdir_count_per_path,
	       pGroupStat->current_write_server,
	       pGroupStat->current_trunk_file_id);

	result = tracker_list_servers(pTrackerServer,
				      pGroupStat->group_name, NULL,
				      storage_infos,
				      FDFS_MAX_SERVERS_EACH_GROUP,
				      &storage_count);
	if (result != 0) {
		return result;
	}

	k = 0;
	pStorageEnd = storage_infos + storage_count;
	for (pStorage = storage_infos; pStorage < pStorageEnd; pStorage++) {
		max_last_source_update = 0;
		for (p = storage_infos; p < pStorageEnd; p++) {
			if (p != pStorage && p->stat.last_source_update
			    > max_last_source_update) {
				max_last_source_update =
				    p->stat.last_source_update;
			}
		}

		pStorageStat = &(pStorage->stat);
		if (max_last_source_update == 0) {
			*szSyncedDelaySeconds = '\0';
		} else {
			if (pStorageStat->last_synced_timestamp == 0) {
				strcpy(szSyncedDelaySeconds,
				       "(never synced)");
			} else {
				int delay_seconds;
				int remain_seconds;
				int day;
				int hour;
				int minute;
				int second;
				char szDelayTime[64];

				delay_seconds =
				    (int) (max_last_source_update -
					   pStorageStat->last_synced_timestamp);
				day = delay_seconds / (24 * 3600);
				remain_seconds =
				    delay_seconds % (24 * 3600);
				hour = remain_seconds / 3600;
				remain_seconds %= 3600;
				minute = remain_seconds / 60;
				second = remain_seconds % 60;

				if (day != 0) {
					sprintf(szDelayTime, "%d days "
						"%02dh:%02dm:%02ds",
						day, hour, minute, second);
				} else if (hour != 0) {
					sprintf(szDelayTime,
						"%02dh:%02dm:%02ds", hour,
						minute, second);
				} else if (minute != 0) {
					sprintf(szDelayTime, "%02dm:%02ds",
						minute, second);
				} else {
					sprintf(szDelayTime, "%ds",
						second);
				}

				sprintf(szSyncedDelaySeconds, "(%s delay)",
					szDelayTime);
			}
		}

		getHostnameByIp(pStorage->ip_addr, szHostname,
				sizeof(szHostname));
		if (*szHostname != '\0') {
			sprintf(szHostnamePrompt, " (%s)", szHostname);
		} else {
			*szHostnamePrompt = '\0';
		}

		if (pStorage->up_time != 0) {
			formatDatetime(pStorage->up_time,
				       "%Y-%m-%d %H:%M:%S",
				       szUpTime, sizeof(szUpTime));
		} else {
			*szUpTime = '\0';
		}

		printf("\tStorage %d:\n"
		       "\t\tid = %s\n"
		       "\t\tip_addr = %s%s  %s\n"
		       "\t\thttp domain = %s\n"
		       "\t\tversion = %s\n"
		       "\t\tjoin time = %s\n"
		       "\t\tup time = %s\n"
		       "\t\ttotal storage = %d MB\n"
		       "\t\tfree storage = %d MB\n"
		       "\t\tupload priority = %d\n"
		       "\t\tstore_path_count = %d\n"
		       "\t\tsubdir_count_per_path = %d\n"
		       "\t\tstorage_port = %d\n"
		       "\t\tstorage_http_port = %d\n"
		       "\t\tcurrent_write_path = %d\n"
		       "\t\tsource storage id = %s\n"
		       "\t\tif_trunk_server = %d\n"
		       "\t\tconnection.alloc_count = %d\n"
		       "\t\tconnection.current_count = %d\n"
		       "\t\tconnection.max_count = %d\n"
		       "\t\ttotal_upload_count = %" PRId64 "\n"
		       "\t\tsuccess_upload_count = %" PRId64 "\n"
		       "\t\ttotal_append_count = %" PRId64 "\n"
		       "\t\tsuccess_append_count = %" PRId64 "\n"
		       "\t\ttotal_modify_count = %" PRId64 "\n"
		       "\t\tsuccess_modify_count = %" PRId64 "\n"
		       "\t\ttotal_truncate_count = %" PRId64 "\n"
		       "\t\tsuccess_truncate_count = %" PRId64 "\n"
		       "\t\ttotal_set_meta_count = %" PRId64 "\n"
		       "\t\tsuccess_set_meta_count = %" PRId64 "\n"
		       "\t\ttotal_delete_count = %" PRId64 "\n"
		       "\t\tsuccess_delete_count = %" PRId64 "\n"
		       "\t\ttotal_download_count = %" PRId64 "\n"
		       "\t\tsuccess_download_count = %" PRId64 "\n"
		       "\t\ttotal_get_meta_count = %" PRId64 "\n"
		       "\t\tsuccess_get_meta_count = %" PRId64 "\n"
		       "\t\ttotal_create_link_count = %" PRId64 "\n"
		       "\t\tsuccess_create_link_count = %" PRId64 "\n"
		       "\t\ttotal_delete_link_count = %" PRId64 "\n"
		       "\t\tsuccess_delete_link_count = %" PRId64 "\n"
		       "\t\ttotal_upload_bytes = %" PRId64 "\n"
		       "\t\tsuccess_upload_bytes = %" PRId64 "\n"
		       "\t\ttotal_append_bytes = %" PRId64 "\n"
		       "\t\tsuccess_append_bytes = %" PRId64 "\n"
		       "\t\ttotal_modify_bytes = %" PRId64 "\n"
		       "\t\tsuccess_modify_bytes = %" PRId64 "\n"
		       "\t\tstotal_download_bytes = %" PRId64 "\n"
		       "\t\tsuccess_download_bytes = %" PRId64 "\n"
		       "\t\ttotal_sync_in_bytes = %" PRId64 "\n"
		       "\t\tsuccess_sync_in_bytes = %" PRId64 "\n"
		       "\t\ttotal_sync_out_bytes = %" PRId64 "\n"
		       "\t\tsuccess_sync_out_bytes = %" PRId64 "\n"
		       "\t\ttotal_file_open_count = %" PRId64 "\n"
		       "\t\tsuccess_file_open_count = %" PRId64 "\n"
		       "\t\ttotal_file_read_count = %" PRId64 "\n"
		       "\t\tsuccess_file_read_count = %" PRId64 "\n"
		       "\t\ttotal_file_write_count = %" PRId64 "\n"
		       "\t\tsuccess_file_write_count = %" PRId64 "\n"
		       "\t\tlast_heart_beat_time = %s\n"
		       "\t\tlast_source_update = %s\n"
		       "\t\tlast_sync_update = %s\n"
		       "\t\tlast_synced_timestamp = %s %s\n",
		       ++k, pStorage->id, pStorage->ip_addr,
		       szHostnamePrompt,
		       get_storage_status_caption(pStorage->status),
		       pStorage->domain_name, pStorage->version,
		       formatDatetime(pStorage->join_time,
				      "%Y-%m-%d %H:%M:%S", szJoinTime,
				      sizeof(szJoinTime)), szUpTime,
		       pStorage->total_mb, pStorage->free_mb,
		       pStorage->upload_priority,
		       pStorage->store_path_count,
		       pStorage->subdir_count_per_path,
		       pStorage->storage_port, pStorage->storage_http_port,
		       pStorage->current_write_path, pStorage->src_id,
		       pStorage->if_trunk_server,
		       pStorageStat->connection.alloc_count,
		       pStorageStat->connection.current_count,
		       pStorageStat->connection.max_count,
		       pStorageStat->total_upload_count,
		       pStorageStat->success_upload_count,
		       pStorageStat->total_append_count,
		       pStorageStat->success_append_count,
		       pStorageStat->total_modify_count,
		       pStorageStat->success_modify_count,
		       pStorageStat->total_truncate_count,
		       pStorageStat->success_truncate_count,
		       pStorageStat->total_set_meta_count,
		       pStorageStat->success_set_meta_count,
		       pStorageStat->total_delete_count,
		       pStorageStat->success_delete_count,
		       pStorageStat->total_download_count,
		       pStorageStat->success_download_count,
		       pStorageStat->total_get_meta_count,
		       pStorageStat->success_get_meta_count,
		       pStorageStat->total_create_link_count,
		       pStorageStat->success_create_link_count,
		       pStorageStat->total_delete_link_count,
		       pStorageStat->success_delete_link_count,
		       pStorageStat->total_upload_bytes,
		       pStorageStat->success_upload_bytes,
		       pStorageStat->total_append_bytes,
		       pStorageStat->success_append_bytes,
		       pStorageStat->total_modify_bytes,
		       pStorageStat->success_modify_bytes,
		       pStorageStat->total_download_bytes,
		       pStorageStat->success_download_bytes,
		       pStorageStat->total_sync_in_bytes,
		       pStorageStat->success_sync_in_bytes,
		       pStorageStat->total_sync_out_bytes,
		       pStorageStat->success_sync_out_bytes,
		       pStorageStat->total_file_open_count,
		       pStorageStat->success_file_open_count,
		       pStorageStat->total_file_read_count,
		       pStorageStat->success_file_read_count,
		       pStorageStat->total_file_write_count,
		       pStorageStat->success_file_write_count,
		       formatDatetime(pStorageStat->last_heart_beat_time,
				      "%Y-%m-%d %H:%M:%S",
				      szLastHeartBeatTime,
				      sizeof(szLastHeartBeatTime)),
		       formatDatetime(pStorageStat->last_source_update,
				      "%Y-%m-%d %H:%M:%S", szSrcUpdTime,
				      sizeof(szSrcUpdTime)),
		       formatDatetime(pStorageStat->last_sync_update,
				      "%Y-%m-%d %H:%M:%S", szSyncUpdTime,
				      sizeof(szSyncUpdTime)),
		       formatDatetime(pStorageStat->last_synced_timestamp,
				      "%Y-%m-%d %H:%M:%S",
				      szSyncedTimestamp,
				      sizeof(szSyncedTimestamp)),
		       szSyncedDelaySeconds);
	}

	return 0;
}

static int list_all_groups(ConnectionInfo * pTrackerServer,
			   const char *group_name)
{
	int result;
	int group_count;
	FDFSGroupStat group_stats[FDFS_MAX_GROUPS];
	FDFSGroupStat *pGroupStat;
	FDFSGroupStat *pGroupEnd;
	int i;

	result = tracker_list_groups(pTrackerServer,
				     group_stats, FDFS_MAX_GROUPS,
				     &group_count);
	if (result != 0) {
		tracker_close_all_connections();
		fdfs_client_destroy();
		return result;
	}

	pGroupEnd = group_stats + group_count;
	if (group_name == NULL) {
		printf("group count: %d\n", group_count);
		i = 0;
		for (pGroupStat = group_stats; pGroupStat < pGroupEnd;
		     pGroupStat++) {
			printf("\nGroup %d:\n", ++i);
			list_storages(pTrackerServer, pGroupStat);
		}
	} else {
		for (pGroupStat = group_stats; pGroupStat < pGroupEnd;
		     pGroupStat++) {
			if (strcmp(pGroupStat->group_name, group_name) ==
			    0) {
				list_storages(pTrackerServer, pGroupStat);
				break;
			}
		}
	}

	return 0;
}
