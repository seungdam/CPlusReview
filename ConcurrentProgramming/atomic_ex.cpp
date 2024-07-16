#include "pch.h"


// 각 스레드는 스레드 별 독립적인 스택영역을 가지나,
// heap 영역과 data 영역에 존재하는 값들에 관해서는 공유한다는 특징을 지님.
// 각 영역에 적재된 자원에 관해 여러 개의 스레드가 이를 접근한다고 하면
// 다양한 문제가 발생할 수 있음 (= Data Race , Race Condition)
// 이때 각 스레드가 동일하게 접근하는 자원에 관해 공유 자원이라 일컬음.

// 그렇기 때문에 멀티 스레드 환경에서 프로그래밍을 수행할 경우,
// 이를 동기화하는 작업이 필요하다.

// Data Race 현상 체크
//int32_t count = 0;

// Atomic을 통해 스레드 동기화 진행
std::atomic<int32_t> count = 0;

void SumWorkerThread()
{
	// 왜 Data Race 현상이 발생한다고 하면
	// 이를 해석하기 위해서는 어셈블리어를 살펴볼 필요가 있다.
	// 실제 내부적으로 동작할 때는 
	// eax = count;
	// eax = eax + 1;
	// count = eax;
	// 3 단계에 걸처서 수행
	// 이 과정에서 스레드별 처리하는 연산 순서가 꼬인다면 제대로 적용안될 수도 있음.

	for (int i = 0; i < 100'0000; ++i)
	{
		++count;
	}
}

void SubWorkerThread()
{
	// 독립적인 스택영역을 가진다 = 해당 스레드 별 지역변수에 관해서는
	// 서로 다른 스레드가 공유할 수 없다는 뜻
	for (int i = 0; i < 10'00000; ++i)
	{
		--count;
	}
}

int main()
{
	std::thread t[2];
	t[0] = std::thread(SumWorkerThread);
	t[1] = std::thread(SubWorkerThread);


	for (int i = 0; i < 2; ++i)
	{
		if (t[i].joinable())
		{
			t[i].join();
		}
	}

	std::cout << "Total Value of Count :" << count;

}