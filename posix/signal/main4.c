#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

void sig_int(int signo)
{
	printf("receive SIGINT\n");
}

int main(int argc, char* argv[])
{
	signal(SIGINT, sig_int);

	int left_second = sleep(3);
	printf("sleep 3 seconds and left %d seconds\n", left_second);


	struct timespec tms, ret_tms;
	tms.tv_sec = 3;
	tms.tv_nsec = 1000 * 1000 * 500;
	if (nanosleep(&tms, &ret_tms) == -1)
	{
		fprintf(stderr, "nanosleep return -1\n");
		printf("return timespec tv_sec=%lu, tv_nsec=%lu\n", ret_tms.tv_sec, ret_tms.tv_nsec);
	}
	else
		printf("nanosleep complete\n");

	return 0;
}

