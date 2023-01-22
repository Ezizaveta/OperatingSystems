#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int parent(int pid)
{
	int status;
	if (waitpid(pid, &status, 0) == -1)
	{
		return 4;
	}
	if (WIFEXITED(status))
	{
		printf("Child's exit status: %d\n", WEXITSTATUS(status));
	}
	//printf("parent process start\n");
	//wait(NULL);
	//printf("parent process finish\n");
	return 0;
}

int child(int argc, char** argv)
{
	execvp(argv[1], (argv+1));
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
		parent(pid);
	}
	else
	{
		child(argc, argv);
	}
	return 0;
}
