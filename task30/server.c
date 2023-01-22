#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <string.h>
#define SIZE 10
char sock_path[] = "./socket";

void custom_unlink(void)
{
	unlink(sock_path);
}

int main(int argc, char** argv)
{
	int fd, cl, rc;
	int socket_server;// = socket(AF_UNIX, SOCK_STREAM, 0);
	if ((socket_server=socket(AF_UNIX, SOCK_STREAM, 0))== -1)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;

	strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path) - 1);
	
	if (bind(socket_server, (struct sockaddr*) &addr, sizeof(addr)) == -1)
	{
		perror("socket bind");
		return 1;
	}
	atexit(custom_unlink);

	if (listen(socket_server, 1) == -1)
	{
		perror("listen");
		return 1;
	}
	struct sockaddr_un client_addr;
	//socklen_t client_addr_len = sizeof(client_addr);
	//int client_sock = accept(socket_server, (struct sockaddr*) &client_addr, &client_addr_len);
	int client_sock = accept(socket_server, NULL, NULL);
	if (client_sock == -1)
	{
		perror("accept");
		if (close(socket_server) < 0)
		{
			perror("server socket close");
		}
		return 1;
	}
	char buf[SIZE];
	char changed[SIZE];
	int size;
	while ((size=read(client_sock, buf, SIZE)) > 0)
	{
		int i = 0;
		for (i = 0; i < size; i++)
		{	
			changed[i] = toupper(buf[i]);
		}
		write(STDOUT_FILENO, changed, size);
	}
	if (size == -1)
	{
		perror("read");
		return 2;
	}
	else if (size == 0)
	{
		printf("End of file\n");
		if (close(client_sock) < 0)
		{
			perror("can't close client");
			return 1;
		}
		if (close(socket_server) < 0)
		{
			perror("close server");
			return 1;
		}

	}
	return 0;
}

