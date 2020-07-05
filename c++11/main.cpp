#include <cstdio>
#include <cstdlib>
#include <thread>
#include <future>
#include <chrono>

void f(std::future<int>& value)
{
	printf("start f\n");
	auto result = value.get();
	printf("get value\n");

	/*
	printf("start2 f\n");
	result = value.get();
	printf("get value\n");
	*/
}

int main(int argc, char* argv[])
{
	std::promise<int> promise;    
	std::future<int> value = promise.get_future(); //将promise与future绑定

	std::thread t1(f, std::ref(value));  //创建线程并且函数传参，ref()是传一个引用
	std::this_thread::sleep_for(std::chrono::seconds(3));
	promise.set_value(3);
	t1.join();

	//system("pause");

	return 0;
}

