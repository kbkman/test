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
	struct sigaction sac;
	sigset_t mask;

	memset((void*)&sac, 0, sizeof(sac));
	sigemptyset(&sac.sa_mask);
	sigaddset(&sac.sa_mask, SIGINT); //在处理SIGQUIT信息时，SIGINT就要阻塞
	sac.sa_handler = sig_quit;
	sac.sa_flags = 0;

	if (sigaction(SIGQUIT, &sac, NULL) < 0)
	{
		perror("sigaction:");
		return 1;
	}

	sigemptyset(&sac.sa_mask);
	sac.sa_handler = sig_int;
	sac.sa_flags = 0;
	if (sigaction(SIGINT, &sac, NULL) < 0)
	{
		perror("sigaction:");
		return 1;
	}

	printf("start sleep\n");
	sleep(10);
	printf("end sleep\n");
	return 0;
}

