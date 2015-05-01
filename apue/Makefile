DEST = 4_9.c 4_12.c 4_16.c 12_8.c 14_21.c
DIRS = -L.
LIBS = -lapue -lpthread -lrt
a.out:
	for i in $(DEST); do \
		clang $$i $(DIRS) $(LIBS);\
	done
