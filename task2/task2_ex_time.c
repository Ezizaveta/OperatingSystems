#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
extern char *tzname[];

int main()
{
	time_t now;
	struct tm *sp;

	(void) time(&now);
	putenv("TZ=America/Los_Angeles");
	//printf("%s", ctime(&now));
	
	sp = localtime(&now);
	printf("%d/%d/%d %d:%d %s\n", sp->tm_mon + 1,
			sp->tm_mday, sp->tm_year, sp->tm_hour,
			sp->tm_min, tzname[sp->tm_isdst]);
	exit(0);
}