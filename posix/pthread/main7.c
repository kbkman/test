#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

void* thread_fun(void* arg)
{
	int id = (int)(long)arg;
	int oldstate;
	//设置为不可取消
	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
	printf("thread fun start %d\n", id);
	sleep(10);
	//pthread_testcancel();//无取消点函数时，可使用pthread_testcancel函数
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

	sleep(2);
	if ((ret = pthread_cancel(tid) != 0))
	{
		fprintf(stderr, "pthread cancel error, %s\n", strerror(ret));
		return 1;
	}
	if ((ret = pthread_cancel(tid2) != 0))
	{
		fprintf(stderr, "pthread cancel error, %s\n", strerror(ret));
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
	return 0;
}

