#include "pch.h"
#include <windows.h>

int32 global;
int32 thread_local tls = 0;

// Window���� Thread���� �Լ��� �Ѱ��� ��, ������ ���� ������ ����� �Ѵ�.
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
	// Window API������ ������ ���� �Լ��� �����Ѵ�. ::CreateThread()
	// 1. thread�� ���� �Ӽ� 
	// 2. �����庰 �Ҵ� ���� ũ�� 
	// 3. �Լ���
	// 4. �Լ� ����
	// 5. ������ ���� �ɼ�
	// 6. ������ ID
	

	//  ������ C/C++ �ڵ�� �ۼ��� ��� ���� ����� �����϶�� �Ѵ�.
	// CRT�Լ��� ����� ��, ������ �߱��ų �� �ֱ� �����̴�.
	
	
	// 
	std::shared_ptr spt = std::make_shared<Base>();

	std::thread t1(WorkerThread<Base>, spt);

	t1.join();
}