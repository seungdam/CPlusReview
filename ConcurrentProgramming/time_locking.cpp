#include "pch.h"
#include <shared_mutex>
#include <vector>

using namespace std;

// 2024-07-29
// *** modern c++ 동시성 프로그래밍 p.87

// reader-writer lock에 관한 이해
// 이 lock에 관해서는 다음과 같은 아이디어와 함께한다.
// Q. 공유 자원은 항상 베타적으로 접근해야할 필요가 있을까?

// A. No 여러 스레드가 공유 자원에 접근한다 하더라도 안전한 상황이 존재한다. \
	바로 공유되는 자원에 관해 읽기만 수행할 경우에는 안전하다.

//  이를 기반으로, 공유 자원에 관해 Read를 수행을 위한 요청에는 잠금을 수행하지 않게해( Write를 위한 잠금 제외)
// 잠금으로 인한 퍼포먼스 저하를 완화 시킬 수 있다는 것.

// std::shared_timed_mutex vs std::shared_mutex
// 둘 다 RWLock의 역할을 수행할 수 있다는 점에서 유사하다.
// 다만 shared_timed_mutex는 C++14, shared_mutex 는 C++17부터 등장했다.
// unique_lock, lock_guard에 넣으면 writer-lock shared_lock에 넣으면 reader-lock의 개념으로 동작한다.
// 
// shared_time_mutex는 shared_mutex와 달리 시간과 관련된 설정이 가능하다는 용이함이 있다. 



// RAII 
// mutex를 날 것으로 활용하는 것은 좋지 않다. ==> Dead Lock의 위험

// 데드락(교착생태)이란?
// 일어나지 않을 일을 계속해서 기다리는 상태를 말한다.

// 1. lock을 수행한 후, unlock을 잊어먹는 경우
// 2. lock을 수행한 후, 자원을 점유하는 과정에서 예외가 발생해 unlock이 제대로 되지않은 경우


shared_timed_mutex stm;

// *** print-color
// \033[background;foreground+m
// \033[0m 해제

void TryWorker()
{
	// unique_lock을 통해 exclusive-lock(=writer-lock) 수행 
	// + defer_lock을 통해 일단 lock 점유를 수행하지 않음
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