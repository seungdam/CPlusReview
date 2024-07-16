#include "pch.h"
#include <windows.h>

int32 global;
int32 thread_local tls = 0;

// Window에서 Thread에게 함수를 넘겨줄 땐, 다음과 같은 형식을 따라야 한다.
DWORD WINAPI WorkerThread(void* arg)
{
	
	for (int i = 0; i < 10'0000; ++i)
	{
		++tls;
	}
	return tls;
}

template<class T>
void WorkerThread(std::shared_ptr<T> ptr)
{
	ptr->task();
}

class Base
{
public:
	void task()
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "Task()\n";
	}
private:
	std::mutex m;

};

int main()
{
	// Window API에서도 스레드 관련 함수를 제공한다. ::CreateThread()
	// 1. thread의 보안 속성 
	// 2. 스레드별 할당 스택 크기 
	// 3. 함수명
	// 4. 함수 인자
	// 5. 스레드 시작 옵션
	// 6. 스레드 ID
	

	//  하지만 C/C++ 코드로 작성할 경우 이의 사용을 지양하라고 한다.
	// CRT함수를 사용할 때, 문제를 야기시킬 수 있기 때문이다.
	
	
	// 
	std::shared_ptr spt = std::make_shared<Base>();

	std::thread t1(WorkerThread<Base>, spt);

	t1.join();
}