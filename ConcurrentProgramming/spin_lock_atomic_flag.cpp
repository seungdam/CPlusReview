
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std;


// *** Sequencial Consistency <== Acquired-Release Sementics ==> Relaxed Sementics
// 우리가 일련의 계약을 느슨하게 조정한다면, 메모리 연산 순서에 관해 조정할 수 있게 된다.


class SpinLock
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	SpinLock()   {}
	

	void lock() { while (flag.test_and_set()) {} }
	// Idea) 처음 lock 수행시 flag -> false값 리턴 후 true로 바뀜. 
	// 다음 사용자가 lock 점유하고자 하면, 무한 루프에 빠지게 됨.
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

	cout << "Mutex 성능 > atomic_flag 성능";
	// 성능은 mutex가 더 낫지만, lock-free 구현이 힘들다는 단점이 존재.
}

// *** atomic vs volatile
// atomic != volatile
// volatile은 컴파일러가 최적화 작업을 수행하는 것을 허용하지 않도록 하는 키워드.
// atomic은 최적화와 관련없이, 스레드 간의 안전한 R/W를 보장하는 키워드.
