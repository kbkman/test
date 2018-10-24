#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <time.h>

void int_handler(int sig_no)
{
	printf("recvieve SIGINT\n");
}

int main(int argc, char* argv[])
{
	//signal(SIGINT, int_handler);

	int ret = poll(NULL, 0, 500);
	if (ret < 0)
		perror("poll:");
	printf("poll return %d\n", ret);

	struct pollfd pfds[10];
	pfds[0].fd = STDIN_FILENO;
	pfds[0].events = POLLIN;
	
	while (1)
	{
		ret = poll(pfds, 1, 5000);
		if (ret < 0)
		{
			perror("poll:");
			break;
		}
		else if (ret == 0)
		{
			printf("poll return timeout\n");
		}
		else
		{
			if (pfds[0].revents & POLLIN)
			{
				printf("can read\n");
				char buf[2] = { 0 };
				ssize_t n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
				if (n > 0)
					printf("stdin:%s\n", buf);
				else
					fprintf(stderr, "stdin read return %ld\n", n);
			}
		}
	}

	return 0;
}

