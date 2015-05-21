.SUFFIXES: .c .o

COMPILE = gcc -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -g -O -DDEBUG_FLAG -DOS_LINUX -DIOEVENT_USE_EPOLL
INC_PATH = -I. -I../../tracker -I../../storage -I../ -I ../../common -I/usr/include -I/usr/include/python2.7 -I/usr/include/fastcommon -I/usr/include/fdfsdfst
LIB_PATH = -L/usr/local/lib -L../ -lfastcommon  -lfdfsclient  -lpthread -ldl -rdynamic -ljsoncpp
#FDFS_SRC_FILES = fastdfs.c
FDFS_SRC_FILES = fastdfstest.c
#FDFS_SHARED_OBJS = fastdfs.o
FDFS_SHARED_OBJS = fastdfstest.o
FDFS_DEST_SHARED_LIBS = fdfsclient.so

$(FDFS_DEST_SHARED_LIBS): $(FDFS_SHARED_OBJS)
	$(COMPILE) -shared $(LIB_PATH) -o $@ $^
$(FDFS_SHARED_OBJS): $(FDFS_SRC_FILES)
	$(COMPILE) -c -fPIC $^ $(INC_PATH) $(LIB_PATH)

clean:
	rm -rf *.o *.so
