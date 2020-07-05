#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

std::condition_variable cv;
std::mutex mx;
void f()
{
	std::unique_lock<std::mutex> locker(mx);
	printf("cv wait\n");
	cv.wait(locker);
	printf("cv wait ok\n");
}

int main(int argc, char* argv[])
{
	std::thread t(f), t2(f);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cv.notify_one();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cv.notify_one();
	t.join();
	t2.join();

	return 0;
}

