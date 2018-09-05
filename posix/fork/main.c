#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	pid_t child_pid = fork();
	if (child_pid == 0)
	{
		printf("child start\n");
		sleep(3);
		printf("child end\n");
		return 100;
	}
	else if (child_pid > 0)
	{
		int status;
		printf("parent start child pid=%u\n", child_pid);
		kill(child_pid, SIGTERM);
		//kill(child_pid, SIGSTOP);

		pid_t pid = wait(&status);
		printf("parent end wait pid=%u\n", pid);
		if (WIFEXITED(status))
			printf("normal exit, exit code=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("signal exit, signal id=%d, core=%d\n", WTERMSIG(status), WCOREDUMP(status));
		else if (WIFSTOPPED(status))
			printf("stopped, stop signal id=%d\n", WSTOPSIG(status));
	}
	else
	{
		perror("fork");
		return 1;
	}

	printf("end\n");
	return 0;
}

