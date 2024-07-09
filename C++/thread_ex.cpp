#include "pch.h"

// <windows.h>에 CreateThread() 메소드가 존재하지만
// 이식성이 좋은 공용 라이브러리 헤더파일을 사용하자

void WorkerThread()
{
	std::cout << "Worker Thread\n";
}

void WorkerThread2(uint32 num)
{
	std::cout << std::this_thread::get_id() << "|"
		<< num <<  "\n";
	
}

void WorkerThread3(int32&& rvnum)
{
	std::cout << ++rvnum;
}

int main()
{
	int32 thread_cnt = std::thread::hardware_concurrency(); // CPU 코어 개수
	std::cout << "Core Count:" << thread_cnt << "\n";

	std::thread t(WorkerThread); // thread 객체의 초기화 방법 1

	std::thread t2; // thread 객체의 초기화 방법 2
	// 이렇게 객체 선언만 선언하는 경우, 스레드 객체는 생성되지만, 실행되지는 않는다.
	t2 = std::thread(WorkerThread); 
	// 이렇게 무명 스레드를 생성하고 이동 대입 연산을 수행해야 비로소 t2가 수행된다.
	
	int a = 10; 
	int& a_ref = a; // a 참조 변수
	
	// thread 객체의 인자로 lvalue 참조타입이 들어갈 수 없다. \
	무조건 rvalue 참조형태로 변경해야 받을 수 있다. \
	이때 rvalue 참조는 완벽한 forwarding을 제공한다고 한다. 

	std::thread t3(WorkerThread3, a_ref);
	

	// *** thread 객체의 경우, 복사 생성자는 제공하지 않는다!!

	std::vector<std::thread> thread_container;
	for (int32_t i = 0; i < 10; ++i)
	{
		thread_container.push_back(std::thread(WorkerThread2, i));
	}

	// t.detach(); 
	// 생성한 스레드 객체를 주 스레드와 분리한다.
	// 하지만 main thread가 종료되면 해당 스레드도 종료된다.
	// Demon Process라고 하기도 한다.
	

	t.join();
	t2.join();
	t3.join();
	
	for (auto& i : thread_container)
	{
		if (i.joinable()) i.join();
	}
	// joinable 해당 스레드에 맡겨놓은 작업이 있는가?
	// join 스레드에 맡겨 놓은 작업이 끝날 때까지 대기
}