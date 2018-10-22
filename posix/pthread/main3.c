#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_rwlock_t locker;
int counter = 0;

void* thread_fun(void* arg)
{
	int id = (int)(long)arg;
	printf("thread fun start %d\n", id);

	pthread_rwlock_wrlock(&locker);
	++counter;
	pthread_rwlock_unlock(&locker);

	pthread_rwlock_rdlock(&locker);
	printf("counter = %d\n", counter);
	pthread_rwlock_unlock(&locker);

	printf("thread fun end, %d\n", id);
	return arg;
}

int main(int argc, char* argv[])
{
	pthread_rwlock_init(&locker, NULL);

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

	pthread_rwlock_destroy(&locker);
	return 0;
}

