#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s string\n", argv[0]);
		exit(1);
	}
	FILE* fpin = popen("./prog", "w");
	if (fpin == NULL)
	{
		perror("pipe");
		exit(2);
	}
	fprintf(fpin, "%s\n", argv[1]);
	if(pclose(fpin))
	{
	       	perror("pipe close");
       	}
	return 0;

};
