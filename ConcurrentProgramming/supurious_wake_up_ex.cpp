#include "pch.h"
#include <condition_variable>
#include <sstream>
#include <queue>
// 2024-07-31

// *** Condition_Varable 조건 변수
// 이벤트 메시지 통지를 통한 스레드 동기화 방식
// 최소 두 개 이상의 스레드가 필요하며, 하나는 수신자(메시지 수신)
// 한 명은 메시지 발신자(메시지 통지)가 되어야한다.


// 2024-08-13
// unique_lock과 함께 사용한다.
// Why? condition_variable::wait(lock, predicate())의 경우, predicate와 같이 활용되는데 
// predicate의 return 값에 따라 참조하는 잠금 객체에 관해 lock(), unlock()을 주기적으로 호출하기 때문이다.
// lock_guard는 중간에 참조하는 잠금 객체에 대해 unlock이 불가능하므로 wait과 함께 사용할 수 없다.

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid(1, 2);
uniform_int_distribution<int> rgb(1, 230);

using namespace std;

// Critical Data
queue<int32> shared_queue;

mutex m;
condition_variable cv;		
condition_variable_any cva; // BasicLockable을 따르는 모든 사용자 정의 객체에서 활용가능



// Condition Variable WorkFlow

// *** 1. Supurious Wake Up
//  통지 없이도 운 좋게 작동되는 경우(스레드 실행 순서를 조정할 경우 확인 가능) 
//  어떤 flag 값을 predicate에서 활용할 때, wait을 호출하기 이전에 이미 조건을 만족하는 경우, 발생한다.					 
 
// *** 2. Lost Wake Up  
// 스레드가 Wait 상태에 진입하기 전, 이미 통지를 보내는 경우. 
// 스레드 실행 순서가 꼬이면 데드락 발생

void Task(int32 color)
{
	auto flag = false;

	for (int32 iter = 0; iter < 5; ++iter)
	{
		if (flag)
		{
			printf("                                                            \r");
			PrintThreadMsg(color, "[Consumer]\033[0m \033[1;33mDo Tasking...\r");
			flag = false;
		}
		else
		{
			printf("                                                            \r");
			PrintThreadMsg(color, "[Consumer]\033[0m \033[1;33mDo Tasking....\r");
			flag = true;
		}

		this_thread::sleep_for(0.3s);
	}
	printf("\n");

	PrintThreadMsg(color, "[Consumer]\033[0m\033[1;33m Job Finishied\n\033[0m");
}

void Producer()
{
	
	auto tcolor = rgb(dre);
	auto elm = 0;
	while (true)
	{
		shared_queue.pop();
		lock_guard<mutex> lg(m);
		shared_queue.push(elm++);
		PrintThreadMsg(tcolor, "[Producer]\033[1;33m Queue Data Set: ", elm , "\033[0m\n");
		cv.notify_one();
		this_thread::sleep_for(0.2s);
		
		
	}
}

void Consumer()
{
	auto tcolor = rgb(dre);
	while (true)
	{
		std::unique_lock<std::mutex> ul(m);
		if (shared_queue.empty())
		{
			cv.wait(ul); 
		}
		
			PrintThreadMsg(tcolor, "[Consumer]\033[1;33m Wake Up ", "\033[0m\n");
			shared_queue.pop();
		
	}
}


int main()
{
	jthread t[5];

	t[0] = jthread(Consumer);
	t[1] = jthread(Consumer);
	t[2] = jthread(Consumer);
	t[3] = jthread(Consumer);
	t[4] = jthread(Producer);
}