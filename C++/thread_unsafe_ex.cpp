#include "pch.h"
#include <chrono>

#define THREAD_CNT 3

// Data Race �߻� Case
// �� �̷� ������ �߻��ϴ°�?
// ��ǻ�� �ý����� ������ �����ϱ� ���� �޸�, ��������, ĳ�� �� �پ��� ��ġ���� ����ϱ� ������
// �����Ͱ� �̵��ϴ� �������� �� ������ ���� �ð� ���̰� �߻��ϰ� �ȴ�.
// �� ������ �� ������ ���� ���̰� �ȴٸ�? �翬�� �������� ��Ȯ���� �������� �ȴ�.


// �ذ� ���
// 1. atomic ���� ���
// 2. ���� ������ ������ ���� ���� TLS(Thread-Local-Storage)�� ������ ��, �۾� �Ϸ� �� �ٽ� ���� �������� ����.
// 3. ������ ������ ���ÿ� join() ȣ���� �����Ͽ� �������� ������ �����ϵ��� �Ѵ�.
// 4. mutex ���� ���

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