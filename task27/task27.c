#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(1);
	}

	char* str = "grep \"^$\" ";
	char grep[strlen(str) + strlen(argv[1]) + 1];
	char* wc = "wc -l";
	memcpy(&grep[0], str, strlen(str));
	memcpy(&grep[strlen(str)], argv[1], strlen(argv[1]));

	FILE* fpin = popen(grep, "r");
	FILE* fpout = popen(wc, "w");
	char line[80];

	while(fgets(line, 80, fpin) != (char *)NULL) {
		fputs(line, fpout);
	}
	pclose(fpin);
	pclose(fpout);
	return 0;

};
