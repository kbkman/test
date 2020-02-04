#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>

void int_handler(int sig_no)
{
	printf("recvieve SIGINT\n");
}

int main(int argc, char* argv[])
{
	/*
	char buf[1024] = { 0 };
	ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
	if (n > 0)
		printf("stdin:%s\n", buf);
	else
		fprintf(stderr, "stdin read return %ld\n", n);
	return 0;
	*/

	signal(SIGINT, int_handler);

	struct timeval tmv;
	tmv.tv_sec = 1;
	tmv.tv_usec = 1 * 1000 * 1000;
	int ret = select(0, 0, 0, 0, &tmv);

	if (ret < 0)
		perror("select:");
	printf("select return %d\n", ret);

	while (1)
	{
		fd_set r_set;
		fd_set w_set;
		FD_ZERO(&r_set);
		FD_ZERO(&w_set);
		FD_SET(STDIN_FILENO, &r_set);
		FD_SET(STDOUT_FILENO, &w_set);

		tmv.tv_sec = 1;
		tmv.tv_usec = 1 * 1000 * 1000;
		ret = select(2, &r_set, &w_set, 0, &tmv);
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

