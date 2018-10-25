#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char msg[] = "test";

	int fd[2];
	if (pipe(fd) != 0)
	{
		perror("pipe:");
		return 1;
	}

	int pid = fork();
	if (pid > 0)
	{
		char buf[1024] = {0};
		ssize_t n = read(fd[0], buf, sizeof(buf));
		if (n < 0) perror("read:");
		printf("read return %ld %s\n", n, buf);
	}
	else if (pid == 0)
	{
		ssize_t n = write(fd[1], msg, sizeof(msg) - 1);
		if (n < 0) perror("write:");
		printf("write return %ld\n", n);
	}
	else
	{
		perror("fork:");
		return 1;
	}
	return 0;
}

