#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>

int fd;
struct flock my_flock;

void sigcatch(int sig)
{
	my_flock.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &my_flock) == 0)
	{
		fprintf(stderr, "file unlocked");
	}
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}
	void (*sig_result)() = sigset(SIGINT, sigcatch);
	if (sig_result == SIG_ERR)
	{	
		perror("sigcatch failed");
		exit(2);
	}
	fd = open(argv[1], O_RDWR);

	if (fd == -1)
	{
		perror("no file");
		return 2;	
	}

	//struct flock my_flock;
	my_flock.l_type = F_WRLCK;
	my_flock.l_whence = SEEK_SET;
	my_flock.l_start = 0;
	my_flock.l_len = 0;
	my_flock.l_pid = getpid();

	if (fcntl(fd, F_SETLK, &my_flock) == -1)
	{
		perror("lock failed");
	//	exit(2);
	}
	else{
		size_t size = strlen("vim ") + strlen(argv[1]) + 1;
		char str[size];
		memcpy(&str, "vim ", strlen("vim "));
		memcpy(&str[strlen("vim ")], argv[1], strlen(argv[1]));
		str[size - 1] = 0;
		system(str);
	}
	my_flock.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &my_flock) == -1)							
	{
		perror("unlock failed");
		exit(2);
	}
	if (close(fd)) {perror("close failed!");}								
	return 0;
}
