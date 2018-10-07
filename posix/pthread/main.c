#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fun(void* arg)
{
	printf("thread fun start\n");
	sleep(3);
	printf("thread fun end\n");
	return (void*)100;
}

int main(int argc, char* argv[])
{
	#ifdef _POSIX_THREADS
	printf("defined _POSIX_THREADS marco\n");
	#endif

	printf("sysconf(_SC_THREADS) return %ld\n", sysconf(_SC_THREADS));

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_fun, (void*)0);
	if (ret)
	{
		fprintf(stderr, "pthread create failed and return %d\n", ret);
		return 1;
	}

	//sleep(6);
	void* thread_ret;
	ret = pthread_join(tid, &thread_ret);
	if (ret)
	{
		fprintf(stderr, "pthread join failed and return %d\n", ret);
		return 1;
	}
	printf("join ok, return %d\n", (int)(long)thread_ret);
	return 0;
}

