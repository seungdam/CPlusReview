#include "pch.h"
#include <shared_mutex>
#include <vector>

using namespace std;

// 2024-07-29
// *** modern c++ ���ü� ���α׷��� p.87

// reader-writer lock�� ���� ����
// �� lock�� ���ؼ��� ������ ���� ���̵��� �Բ��Ѵ�.
// Q. ���� �ڿ��� �׻� ��Ÿ������ �����ؾ��� �ʿ䰡 ������?

// A. No ���� �����尡 ���� �ڿ��� �����Ѵ� �ϴ��� ������ ��Ȳ�� �����Ѵ�. \
	�ٷ� �����Ǵ� �ڿ��� ���� �б⸸ ������ ��쿡�� �����ϴ�.

//  �̸� �������, ���� �ڿ��� ���� Read�� ������ ���� ��û���� ����� �������� �ʰ���( Write�� ���� ��� ����)
// ������� ���� �����ս� ���ϸ� ��ȭ ��ų �� �ִٴ� ��.

// std::shared_timed_mutex vs std::shared_mutex
// �� �� RWLock�� ������ ������ �� �ִٴ� ������ �����ϴ�.
// �ٸ� shared_timed_mutex�� C++14, shared_mutex �� C++17���� �����ߴ�.
// unique_lock, lock_guard�� ������ writer-lock shared_lock�� ������ reader-lock�� �������� �����Ѵ�.
// 
// shared_time_mutex�� shared_mutex�� �޸� �ð��� ���õ� ������ �����ϴٴ� �������� �ִ�. 



// RAII 
// mutex�� �� ������ Ȱ���ϴ� ���� ���� �ʴ�. ==> Dead Lock�� ����

// �����(��������)�̶�?
// �Ͼ�� ���� ���� ����ؼ� ��ٸ��� ���¸� ���Ѵ�.

// 1. lock�� ������ ��, unlock�� �ؾ�Դ� ���
// 2. lock�� ������ ��, �ڿ��� �����ϴ� �������� ���ܰ� �߻��� unlock�� ����� �������� ���


shared_timed_mutex stm;

// *** print-color
// \033[background;foreground+m
// \033[0m ����

void TryWorker()
{
	// unique_lock�� ���� exclusive-lock(=writer-lock) ���� 
	// + defer_lock�� ���� �ϴ� lock ������ �������� ����
	std::unique_lock<std::shared_timed_mutex> sl(stm,std::defer_lock);
	if (sl.try_lock_for(3s))
	{
		
		cout << "\033[1;4;32m" << this_thread::get_id() << "]\033[0m" << " Get Sleeping...\n";
		this_thread::sleep_for(5s);
	}
	else
	{
		std::cout << "\033[1;4;35m" << this_thread::get_id() << "\033[0m" << "] Get Lock Failed.\n";
	}

}

struct Locker
{
	mutex m;
	string name;
};

void DeadLock(mutex& l1, mutex& l2)
{
	
}

int main()
{
	std::vector<std::thread> ts;
	for (int32 i = 0; i < 100; ++i)
	{
		ts.push_back(thread(TryWorker));
		this_thread::sleep_for(1s);
	}

	for(auto& i : ts)
	{
		i.join();
	}
}