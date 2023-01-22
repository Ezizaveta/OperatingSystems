#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define SIZE 10

int main()
{
	char buf[SIZE];
	char changed[SIZE+1];
	ssize_t size;
	while ((size=read(STDIN_FILENO, buf, SIZE)) > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			changed[i] = toupper(buf[i]);
		}
	//	changed[size] = 0;
		write(STDOUT_FILENO, changed, size);
	}
	return 0;
}
