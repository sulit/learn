#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINEBUF 1024
#define MAXLINENUM 10000
#define BUFSIZE 20480
#define RUNTIME 60

void usage();
int getrandomline(const char *filename, char readbuf[]);

int
main(int argc, char *argv[])
{
	time_t jobstart, jobend;
	struct timeval start, end;
	long long startusec, endusec;
	int fd;
	int wrfd;
	char filename[MAXLINEBUF]={0};
	char readbuf[BUFSIZE];
	char writebuf[BUFSIZE];

	double elapsed;

	if (argc != 2)
		usage();

	srand((unsigned int)time(NULL));
	jobstart = time(NULL);
	sprintf(writebuf, "echo > /dev/shm/outtime.txt");
	system(writebuf);

	while ((int)difftime(jobend, jobstart) < RUNTIME)
	{
		if (getrandomline(argv[1], readbuf))
		{
			fprintf(stderr, "read random line error\n");
			exit(1);
		}

		sprintf(filename, "%s", readbuf);

		gettimeofday(&start, NULL);

		if ((fd = open(filename, O_RDONLY)) == -1)
		{
			fprintf(stderr, "open file %s error\n", filename);
			exit(1);
		}

		read(fd, readbuf, BUFSIZE);
		
		if (fd != -1)
			close(fd);

		gettimeofday(&start, NULL);

		startusec = start.tv_sec * 1000000 + start.tv_usec;
		endusec = end.tv_sec * 1000000 + end.tv_usec;
		elapsed = (double)(endusec - startusec) / 1000000.0;
		printf("%.6f\n", elapsed);
		sprintf(writebuf, "echo %.6f >> /dev/shm/outtime.txt", elapsed);
		system(writebuf);

		jobend = time(NULL);
		printf("difftime %f\n", difftime(jobend, jobstart));
	}

	exit(0);
}

void
usage()
{
	fprintf(stderr, "usage: ./filedo FILENAME");
	exit(1);
}

int
getrandomline(const char *filename, char readbuf[])
{
	FILE *fp;
	long linenum;
	long linecount;

	linenum = rand() % MAXLINENUM + 1;
	printf("select %ld line\n", linenum);
	
	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "open %s error \n", filename);
		exit(1);
	}

	for (linecount=0; linecount <= linenum; linecount++)
		fgets(readbuf, MAXLINEBUF, fp);

	if (fp)
		fclose(fp);
	readbuf[strlen(readbuf)-1] = '\0';

	return 0;
}
