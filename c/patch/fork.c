#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t result;

	result = fork();

	if (result == -1)
	{
		printf("Fork error\n");
	}
	else if (result == 0)
	{
		printf("The returned value is %d\nIn child process!!\nMy PID is %d\n", result, getpid());
	}
	else
	{
		printf("The returned value is %d\nIn father process!!\nMy PID is %d\n", result, getpid());
	}
	printf("print test\n"); // NOTE: do twice

	return result;
}
