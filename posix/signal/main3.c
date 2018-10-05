#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void sig_quit(int sig_no)
{
	printf("get SIGQUIT signal\n");
	sleep(5);
	printf("get SIGQUIT signal end\n");
}

static void sig_int(int sig_no)
{
	printf("get SIGINT signal\n");
}

int main(int argc, char* argv[])
{
	sigset_t newmask, oldmask, suspendmask;

	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	printf("set proc mask\n");
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		fprintf(stderr, "sigprocmask failed\n");
		return 2;
	}

	printf("my code\n");
	sleep(5);
	printf("my code end\n");

	printf("sigsuspend\n");
	sigemptyset(&suspendmask);
	sigaddset(&suspendmask, SIGINT);
	sigsuspend(&suspendmask); 
	//sigsuspend(&oldmask); 
	printf("sigsuspend end\n");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		fprintf(stderr, "sigprocmask failed\n");
		return 2;
	}
	sleep(5);

	return 0;
}

