#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void file_process(const char* file_name)
{
	FILE* file = fopen(file_name, "a+");
	if (file = NULL)
	{
		perror("Can't open file!\n");
	}
	else
	{
		printf("File is opened\n");
		fclose(file);
	}
}



void print_uid()
{
	printf("Real userID: %d\n", getuid());
	printf("Effective userID: %d\n", geteuid());
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		exit(0);
	}
	printf("Real uid: %d\n", getuid());
	printf("Effective uid: %d\n", geteuid());
	//print_uid();
	file_process(argv[1]);
	seteuid(geteuid());
	//print_uid();
	printf("real uid: %d\n", getuid());
	printf("effective: %d\n", geteuid());
	file_process(argv[1]);
	return 0;
}

