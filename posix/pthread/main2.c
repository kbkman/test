#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t locker;
int counter = 0;

void* thread_fun(void* arg)
{
	int id = (int)(long)arg;
	printf("thread fun start %d\n", id);

	while (counter < 10000)
	{
		printf("counter=%d, tid=%d\n", counter, id);
		if (pthread_mutex_trylock(&locker) == 0)
		{
			++counter;
			pthread_mutex_unlock(&locker);
		}
		else
		{
			printf("try lock failed %d\n", id);
		}
	}

	printf("thread fun end, %d\n", id);
	return arg;
}

int main(int argc, char* argv[])
{
	pthread_mutex_init(&locker, NULL);
	/*
	printf("aaa\n");
	pthread_mutex_lock(&locker);
	printf("bbb\n");
	pthread_mutex_lock(&locker);
	printf("ccc\n");
	*/
	pthread_t tid, tid2;
	int ret = pthread_create(&tid, NULL, thread_fun, (void*)1);
	if (ret)
	{
		fprintf(stderr, "pthread create thread failed and return %d\n", ret);
		return 1;
	}

	ret = pthread_create(&tid2, NULL, thread_fun, (void*)2);
	if (ret)
	{
		fprintf(stderr, "pthread create thread2 failed and return %d\n", ret);
		return 1;
	}

	void* thread_ret;
	ret = pthread_join(tid, &thread_ret);
	if (ret)
	{
		fprintf(stderr, "pthread join thread failed and return %d\n", ret);
		return 1;
	}
	printf("join thread ok, return %d\n", (int)(long)thread_ret);

	ret = pthread_join(tid2, &thread_ret);
	if (ret)
	{
		fprintf(stderr, "pthread join thread2 failed and return %d\n", ret);
		return 1;
	}
	printf("join thread2 ok, return %d\n", (int)(long)thread_ret);

	pthread_mutex_destroy(&locker);
	return 0;
}

