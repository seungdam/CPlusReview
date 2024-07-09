#include "pch.h"

// <windows.h>�� CreateThread() �޼ҵ尡 ����������
// �̽ļ��� ���� ���� ���̺귯�� ��������� �������

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
	int32 thread_cnt = std::thread::hardware_concurrency(); // CPU �ھ� ����
	std::cout << "Core Count:" << thread_cnt << "\n";

	std::thread t(WorkerThread); // thread ��ü�� �ʱ�ȭ ��� 1

	std::thread t2; // thread ��ü�� �ʱ�ȭ ��� 2
	// �̷��� ��ü ���� �����ϴ� ���, ������ ��ü�� ����������, ��������� �ʴ´�.
	t2 = std::thread(WorkerThread); 
	// �̷��� ���� �����带 �����ϰ� �̵� ���� ������ �����ؾ� ��μ� t2�� ����ȴ�.
	
	int a = 10; 
	int& a_ref = a; // a ���� ����
	
	// thread ��ü�� ���ڷ� lvalue ����Ÿ���� �� �� ����. \
	������ rvalue �������·� �����ؾ� ���� �� �ִ�. \
	�̶� rvalue ������ �Ϻ��� forwarding�� �����Ѵٰ� �Ѵ�. 

	std::thread t3(WorkerThread3, a_ref);
	

	// *** thread ��ü�� ���, ���� �����ڴ� �������� �ʴ´�!!

	std::vector<std::thread> thread_container;
	for (int32_t i = 0; i < 10; ++i)
	{
		thread_container.push_back(std::thread(WorkerThread2, i));
	}

	// t.detach(); 
	// ������ ������ ��ü�� �� ������� �и��Ѵ�.
	// ������ main thread�� ����Ǹ� �ش� �����嵵 ����ȴ�.
	// Demon Process��� �ϱ⵵ �Ѵ�.
	

	t.join();
	t2.join();
	t3.join();
	
	for (auto& i : thread_container)
	{
		if (i.joinable()) i.join();
	}
	// joinable �ش� �����忡 �ðܳ��� �۾��� �ִ°�?
	// join �����忡 �ð� ���� �۾��� ���� ������ ���
}