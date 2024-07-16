#include "pch.h"
#include <chrono>

#define THREAD_CNT 2


int32 global = 0;


void WorkerThread(int32 id, int32 loopsCnt)
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
		t[i].join();
	}

	// �̷��� �����ҰŸ� ���� ������ ������ �� ����. ���� Bad�� ���
	printf("%d", global);
}