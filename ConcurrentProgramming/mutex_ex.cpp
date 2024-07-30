#include "pch.h"


std::mutex mlock;
std::vector<int32> v;

// RAII Pattern을 통한 Lock 관리방법
// std::lock_guard<std::mutex> lg(mlock);
// std::unique_lock<std::mutex> ul(mlock, std::defer_lock);  
// std::defer_lock  \
	--> lock에 관한 option에 해당한다.



void Push(int32_t num)
{
	while (true)
	{
		mlock.lock();
		v.push_back(num);
		std::cout << "Push" << num << "\n";
		mlock.unlock();
	}
}

void Pop()
{
	while (true)
	{
		mlock.lock();
		if(v.size() > 0) v.pop_back();
		std::cout << "Pop\n";
		mlock.unlock();
	}
}

int main()
{
	std::thread t1(Push,1);
	std::thread t2(Pop);

	t1.join();
	t2.join();
}