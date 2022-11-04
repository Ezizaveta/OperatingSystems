#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc!=3)
	{
		printf("usage: %s *file name* number of lines\n", argv[0]);
		return 1;	
	}		
	if (!isdigit(*argv[2]))
	{
		return 2;
	}
	FILE* fp;
	fp = fopen(argv[1], "w");
	if (!fp)
	{
		return 3;
	}

	for (int i = 0; i < strtol(argv[2], NULL, 10); ++i)	
	{
		fprintf(fp,"string number %d\n",i);
	}

	return 0;
}
