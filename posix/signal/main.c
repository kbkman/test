#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_quit(int sig_no)
{
	printf("get SIG_QUIT signal\n");
}

int main(int argc, char* argv[])
{
	sigset_t newmask, oldmask, pendmask;
	int i;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
	{
		fprintf(stderr, "signal(SIGQUIT) failed\n");
		return 1;
	}

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		fprintf(stderr, "sigprocmask failed\n");
		return 2;
	}

	sleep(5);

	if (sigpending(&pendmask) < 0)
	{
		fprintf(stderr, "sigpending failed\n");
		return 3;
	}
	if (sigismember(&pendmask, SIGINT))
		printf("SIGINT signal pending\n");
	if (sigismember(&pendmask, SIGQUIT))
		printf("SIGQUIT signal pending\n");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		fprintf(stderr, "sigprocmask failed\n");
		return 4;
	}

	for (i = 0; i < 100; i++)
	{
		printf("sleep 1\n");
		sleep(1);
	}

	return 0;
}

