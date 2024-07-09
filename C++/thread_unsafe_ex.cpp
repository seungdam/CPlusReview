#include "pch.h"
#include <chrono>

#define THREAD_CNT 3

// Data Race 발생 Case
// 왜 이런 현상이 발생하는가?
// 컴퓨터 시스템은 연산을 수행하기 위해 메모리, 레지스터, 캐시 등 다양한 장치들을 사용하기 때문에
// 데이터가 이동하는 과정에서 각 스레드 별로 시간 차이가 발생하게 된다.
// 그 과정이 각 스레드 별로 꼬이게 된다면? 당연히 데이터의 정확성이 떨어지게 된다.


// 해결 방안
// 1. atomic 변수 사용
// 2. 공유 변수를 스레드 지역 변수 TLS(Thread-Local-Storage)로 변경한 후, 작업 완료 후 다시 공유 변수에게 전달.
// 3. 스레드 생성과 동시에 join() 호출을 수행하여 순차적인 접근이 가능하도록 한다.
// 4. mutex 변수 사용

int32 global = 0;


void WorkerThread(int32 id ,int32 loopsCnt)
{

	for (int32 i = 0; i < loopsCnt; ++i)
	{
		++global;
		if (!(i % 10)) std::this_thread::yield();
	}
	printf("%d. %d\n", id, global);
}

int main()
{
	std::thread t[THREAD_CNT];

	for (int32 i = 0; i < THREAD_CNT; ++i)
	{
		t[i] = std::thread(WorkerThread, i, 10'000);
	}

	for (int32 i = 0; i < THREAD_CNT; ++i)
	{
	
		if (i % 2 == 0)
		{
			t[i].detach();
		}
		else
		{
			t[i].join();
		}
	}

	printf("%d", global);
}