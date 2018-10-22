#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t locker;
pthread_cond_t cond;
int stop_app = 0;
int counter = 0;

void* control_thread_fun(void* arg)
{
	printf("control thread fun start\n");
	sleep(2);
	pthread_mutex_lock(&locker);
	stop_app = 1;
	//pthread_cond_signal(&cond);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&locker);
	/*
	sleep(5);
	pthread_cond_signal(&cond);
	*/
	printf("control thread fun end\n");
	return arg;
}

void* thread_fun(void* arg)
{
	int id = (int)(long)arg;

	pthread_mutex_lock(&locker);
	printf("thread fun start %d\n", id);
	while (!stop_app)
		pthread_cond_wait(&cond, &locker);
	pthread_mutex_unlock(&locker);

	printf("thread fun end, %d\n", id);
	return arg;
}

int main(int argc, char* argv[])
{
	pthread_mutex_init(&locker, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_t ctid;
	int ret = pthread_create(&ctid, NULL, control_thread_fun, (void*)0);
	if (ret)
	{
		fprintf(stderr, "pthread create control thread failed and return %d\n", ret);
		return 1;
	}

	pthread_t tid;
	ret = pthread_create(&tid, NULL, thread_fun, (void*)1);
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
	ret = pthread_join(ctid, &thread_ret);
	if (ret)
	{
		fprintf(stderr, "pthread join control thread failed and return %d\n", ret);
		return 1;
	}

	printf("join control thread ok, return %d\n", (int)(long)thread_ret);
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

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&locker);
	return 0;
}

