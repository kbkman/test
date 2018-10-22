#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_key_t thread_key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;

void thread_init(void)
{
	if (pthread_key_create(&thread_key, NULL) != 0)
	{
		fprintf(stderr, "pthread_key_create error\n");
		exit(1);
	}
}

void* thread_fun(void* arg)
{
	pthread_once(&init_done, thread_init);
	int id = (int)(long)arg;
	pthread_setspecific(thread_key, arg);

	printf("thread fun start %d\n", id);
	for (int i = 0; i < 5; ++i)
	{
		printf("tid=%d, thread key value=%d\n", id, (int)(long)pthread_getspecific(thread_key));
		sleep(1);
	}
	printf("thread fun end, %d\n", id);
	return arg;
}

int main(int argc, char* argv[])
{
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

	pthread_key_delete(thread_key);
	return 0;
}

