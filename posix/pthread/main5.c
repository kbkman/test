#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_spinlock_t locker;

void* thread_fun(void* arg)
{
	int id = (int)(long)arg;

	printf("thread fun start %d\n", id);
	pthread_spin_lock(&locker);
	sleep(5);
	pthread_spin_unlock(&locker);
	printf("thread fun end, %d\n", id);
	return arg;
}

int main(int argc, char* argv[])
{
	pthread_spin_init(&locker, PTHREAD_PROCESS_PRIVATE);

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_fun, (void*)1);
	if (ret)
	{
		fprintf(stderr, "pthread create thread failed and return %d\n", ret);
		return 1;
	}

	pthread_t tid2;
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

	pthread_spin_destroy(&locker);
	return 0;
}

