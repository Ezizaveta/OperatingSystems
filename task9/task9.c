#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int parent(void)
{
	printf("parent process start\n");
	wait(NULL);
	printf("parent process finish\n");
	return 0;
}

int child(int argc, char** argv)
{
	execlp("/bin/cat", "cat", argv[1], NULL);
	//fprintf("exec failed!");
	perror("exec failed!");
	exit(3);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s file_name\n", argv[0]);
		exit(1);
	}

	pid_t pid = fork();
	
	if (pid < 0)
	{
		perror("fork failed!");
		exit(2);
	}
	else if (pid > 0)
	{
		parent();
	}
	else
	{
		child(argc, argv);
	}
	return 0;
}
