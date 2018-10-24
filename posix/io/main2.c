#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <time.h>

void int_handler(int sig_no)
{
	printf("recvieve SIGINT\n");
}

int main(int argc, char* argv[])
{
	//signal(SIGINT, int_handler);

	struct timespec tms;
	tms.tv_sec = 2;
	tms.tv_nsec = 0;
	sigset_t mysigset;
	sigemptyset(&mysigset);
	sigaddset(&mysigset, SIGINT);
	int ret = pselect(1, 0, 0, 0, &tms, &mysigset);
	if (ret < 0)
		perror("pselect:");
	printf("pselect return %d\n", ret);

	while (1)
	{
		fd_set r_set;
		fd_set w_set;
		FD_ZERO(&r_set);
		FD_ZERO(&w_set);
		FD_SET(STDIN_FILENO, &r_set);
		FD_SET(STDOUT_FILENO, &w_set);

		ret = pselect(2, &r_set, &w_set, 0, &tms, NULL);
		if (ret < 0)
		{
			perror("select:");
			break;
		}
		else if (ret == 0)
		{
			printf("select return timeout\n");
		}
		else
		{
			if (FD_ISSET(STDIN_FILENO, &r_set))
			{
				printf("can read\n");
				char buf[1024] = { 0 };
				ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
				if (n > 0)
					printf("stdin:%s\n", buf);
				else
					fprintf(stderr, "stdin read return %ld\n", n);
			}
			if (FD_ISSET(STDOUT_FILENO, &w_set))
			{
				printf("can write\n");
			}
			
		}
	}

	return 0;
}

