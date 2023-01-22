#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

char socket_path[] = "./socket";

int main(int argc, char** argv)
{

	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("socket");
		return 2;
	}
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
	{
		perror("connect error");
		return 2;
	}
	char buf[SIZE];
	int size;
	while((size=read(STDIN_FILENO, buf, sizeof(buf))) > 0) 
	{
		write(fd, buf, size);
	}
	if (close(fd) < 0)
	{
		perror("close socket");
		return 3;
	}
      	return 0;
}
