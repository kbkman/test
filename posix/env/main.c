#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void setmyenv(void)
{
	//char kv[] = "BLUE=kbkman";
	char* kv = "BLUE=kbkman";
	putenv(kv);

	char kv2[] = "kbkman";
	setenv("oray", kv2, 1);
	setenv("HOME", "hello", 1);
}

int main(int argc, char* argv[])
{
	char* val = getenv("HOME");
	if (!val)
	{
		perror("getenv HOME");
		return 1;
	}
	printf("HOME=%s\n", val);

	setmyenv();
	val = getenv("BLUE");
	if (!val)
	{
		perror("getenv BLUE");
		return 1;
	}
	printf("BLUE=%s\n", val);

	val = getenv("oray");
	if (!val)
	{
		perror("getenv oray");
		return 1;
	}
	printf("oray=%s\n", val);
	printf("HOME=%s\n", getenv("HOME"));
	return 0;
}

