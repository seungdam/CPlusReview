
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std;


// *** Sequencial Consistency <== Acquired-Release Sementics ==> Relaxed Sementics
// �츮�� �Ϸ��� ����� �����ϰ� �����Ѵٸ�, �޸� ���� ������ ���� ������ �� �ְ� �ȴ�.


class SpinLock
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	SpinLock()   {}
	

	void lock() { while (flag.test_and_set()) {} }
	// Idea) ó�� lock ����� flag -> false�� ���� �� true�� �ٲ�. 
	// ���� ����ڰ� lock �����ϰ��� �ϸ�, ���� ������ ������ ��.
	void unlock() { flag.clear(); } // false -> true 
};

SpinLock sl;
mutex m;
int cnt = 0;




void WorkerThread()
{
	sl.lock();
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	sl.unlock();
}

void WorkerThread2()
{
	m.lock();
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	m.unlock();
}

int main()
{
	thread t1(WorkerThread2);
	thread t2(WorkerThread2);
	
	t1.join();
	t2.join();

	cout << "Mutex ���� > atomic_flag ����";
	// ������ mutex�� �� ������, lock-free ������ ����ٴ� ������ ����.
}

// *** atomic vs volatile
// atomic != volatile
// volatile�� �����Ϸ��� ����ȭ �۾��� �����ϴ� ���� ������� �ʵ��� �ϴ� Ű����.
// atomic�� ����ȭ�� ���þ���, ������ ���� ������ R/W�� �����ϴ� Ű����.
