#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		char buf[128];
		sprintf(buf, "arg%d=%s\n", i, argv[i]);
		printf(buf);
	}

	extern char** environ;
	char** ptr;
	for (ptr = environ; *ptr != 0; ptr++)
		printf("%s\n", *ptr);

	return 10;
}

