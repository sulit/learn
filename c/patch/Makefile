DIFFFILES = fork.c fork2.c
SRCFILE = fork.c
PATCHFILE = fork.patch
DESTFILE = fork
CC = clang

difffiles:
	diff -u $(DIFFFILES) > $(PATCHFILE)
patchfiles:
	patch -b $(SRCFILE) $(PATCHFILE)
compile:
	$(CC) $(SRCFILE) -o $(DESTFILE)
clean:
	cp $(SRCFILE).orig $(SRCFILE); rm $(PATCHFILE) $(DESTFILE) $(SRCFILE).orig
