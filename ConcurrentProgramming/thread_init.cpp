#include "pch.h"

// <windows.h>에 CreateThread() 메소드가 존재하지만
// 이식성이 좋은 공용 라이브러리 헤더파일을 사용하자

void Task()
{
	std::cout << "Do Task\n";
}

void PrintTheadIdTask(uint32 num)
{
	std::cout << std::this_thread::get_id() << "|"
		<< num <<  "\n";
	
}

int main()
{
	int32 thread_cnt = std::thread::hardware_concurrency(); // CPU 코어 개수
	std::cout << "Core Count:" << thread_cnt << "\n";

	std::thread t(Task); // thread 객체의 초기화 방법 1

	std::thread t2; // thread 객체의 초기화 방법 2
	// 이렇게 객체 선언만 선언하는 경우, 스레드 객체는 생성되지만, 실행되지는 않는다.
	t2 = std::thread(Task); 
	// 이렇게 무명 스레드를 생성하고 이동 대입 연산을 수행해야 비로소 t2가 수행된다.
	
	
}