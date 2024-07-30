#include "pch.h"
class TryWorker // Make Callable Unit Object Class
{
public:
	TryWorker(const int32& id) : tid(id)
	{
	}
	void operator()()  // () Operator overloading for std::thread
	{
		for(int32 iter = 0; iter <= 3; ++iter)
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << tid << "] Work Done\n";
	}
private:
	int32 tid;
};

int main()
{

	// *** cout은 애초에 thread-safe 한 것. 다만 Race-Condition 즉, 경쟁상태로 인해서
	// 화면에 보이는 쓰기작업 자체는 교차적으로 수행된다는 것이다.
	// 그렇기 때문에 전역 스트림 객체(cout,cin ...etc)에 관해 mutex를 사용하는 것은 적절하지 않은 행위이다.

	std::thread worker[50];

	for (int32 iter = 0; iter < 50; ++iter)
	{
		worker[iter] =  std::thread(TryWorker(iter));
	}
	
	for (auto& i : worker)
	{
		i.join();
	}
}