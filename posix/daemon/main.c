#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void info(int fd)
{
	struct flock fl;
	memset(&fl, 0, sizeof(fl));
	int ret = fcntl(fd, F_GETLK, &fl);
	if (ret < 0)
	{
		perror("fcntl F_GETLK:");
		close(fd);
		exit(1);
	}
	printf("pid=%u, l_type=%s, l_start=%ld, l_whence=%d, l_pid=%u\n",
		getpid(),
		fl.l_type == F_RDLCK ? "F_RDLCK" : (fl.l_type == F_WRLCK ? "F_WRLCK" : "F_UNLCK"),
		fl.l_start,
		fl.l_whence,
		fl.l_pid);
}

int main(int argc, char* argv[])
{
	int fd = open("/tmp/mtest", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		perror("open:");
		return 1;
	}

	info(fd);

	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	fl.l_pid = 0;
	int ret = fcntl(fd, F_SETLK, &fl);
	if (ret < 0)
	{
		perror("fcntl F_SETLK:");
		close(fd);
		return 1;
	}

	info(fd);

	sleep(1000);
	close(fd);
	return 0;
}

