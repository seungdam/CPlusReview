#include "pch.h"
#include <chrono>

#define THREAD_CNT 4


// TLS 변수 생성
thread_local int32 tls;
int32 global = 0;


void WorkerThread(int32 id, int32 loopsCnt)
{

	tls = global;
	for (int32 i = 0; i < loopsCnt; ++i)
	{
		tls++;
		if (!(i % 10)) std::this_thread::yield();
	}
	global += tls;
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
		t[i].join();
	}

	// 이렇게 구현할거면 단일 스레드 구현이 더 낫다. ㅋㅋ Bad한 방법
	printf("%d", global);
}