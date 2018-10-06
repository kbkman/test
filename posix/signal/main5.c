#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char* argv[])
{
	psignal(SIGQUIT, "SIGQUIT");
	psignal(SIGINT, "SIGINT");

	printf("SIGSTOP:%s\n", strsignal(SIGSTOP));
	printf("SIGCONT:%s\n", strsignal(SIGCONT));

	for (int i = 1; i <= 64; ++i)
		printf("signal=%d:%s\n", i, strsignal(i));

	return 0;
}

