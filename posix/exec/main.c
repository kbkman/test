#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/times.h>

int main(int argc, char* argv[])
{
	struct tms tmsbuf_start, tmsbuf_end;
	clock_t clk = times(&tmsbuf_start);
	pid_t child_pid = fork();
	if (child_pid == 0)
	{
		/*
		if (execlp("cat", "cat", "main.c", (char*)0) == -1)
		*/
		char* myargv[] = {
			"USER=kbkman",
			"name=BLUE",
			NULL,
		};
		if (execle("./test.sh", "./test.sh", "main.c", "test", (char*)0, myargv) == -1)
			perror("exec:");

		_exit(100);
		return 100;
	}
	else if (child_pid > 0)
	{
		int status;
		printf("parent start child pid=%u\n", child_pid);

		char* login_name = getlogin();
		printf("login name=%s\n", login_name);
		printf("login uid=%d\n", getuid());
		printf("NZERO=%ld\n", sysconf(_SC_NZERO));
		printf("self nice=%d\n", getpriority(PRIO_PROCESS, getpid()));

		pid_t pid = wait(&status);
		printf("parent end wait pid=%u\n", pid);
		if (WIFEXITED(status))
			printf("normal exit, exit code=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("signal exit, signal id=%d, core=%d\n", WTERMSIG(status), WCOREDUMP(status));
		else if (WIFSTOPPED(status))
			printf("stopped, stop signal id=%d\n", WSTOPSIG(status));

		printf("times return %ld\n", times(&tmsbuf_end) - clk);
		printf("user cpu time=%ld\n", tmsbuf_end.tms_utime - tmsbuf_start.tms_utime);
		printf("system cpu time=%ld\n", tmsbuf_end.tms_stime - tmsbuf_start.tms_stime);
		printf("%ld clk peer second\n", sysconf(_SC_CLK_TCK));
	}
	else
	{
		perror("fork");
		return 1;
	}

	printf("end\n");
	return 0;
}

