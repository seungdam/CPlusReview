#include "pch.h"
#include <condition_variable>
#include <sstream>

// 2024-07-31

// *** Condition_Varable 조건 변수
// 이벤트 메시지 통지를 통한 스레드 동기화 방식
// 최소 두 개 이상의 스레드가 필요하며, 하나는 수신자(메시지 수신)
// 한 명은 메시지 발신자(메시지 통지)가 되어야한다.


// 보편적으로 unique_lock과 함께 사용된다는 특징이 있다.



using namespace std;

// Critical Data
bool shared_data{ false };

mutex m;
condition_variable cv;		// unique_lock만 가능
condition_variable_any cva; // BasicLockable을 따르는 모든 사용자 정의 객체에서 활용가능


void Task()
{
	for (int32 i = 0; i < 3; ++i)
	{
		printf("\r\033[1;31mDo Tasking ...\033[0m\r");
		this_thread::sleep_for(0.2s);
	}
	printf("\n");
}

void Producer()
{
	{	
		lock_guard lg(m);
		printf(t_set t_color_r "LG Locked.\n" t_reset);
		printf("[\033[33m Semder \033[0m] : Data Setting...\n");
		this_thread::sleep_for(0.3s);
		shared_data = true;
		printf(t_set t_color_r "LG UnLocked.\n" t_reset);
	}
	printf("[\033[33m Semder \033[0m] : Data Ready.\n");
	cv.notify_all();

}

void Consumer()
{
	stringstream ss;
	ss << this_thread::get_id();
	printf("[\033[33mReceiver\033[0m] : Waiting Job.\n");
	std::unique_lock<std::mutex> ul(m); 
	printf(t_set t_color_g "[%s]" t_reset t_set t_color_r " UL Locked.\n" t_reset, ss.str().c_str());
	cv.wait(ul, [] { return shared_data; }); 

	/* Same as below code
	
	while ([&]{return shared_data;}())
	{
		cv.wait(ul);
	}
	*/


	// *** Supurious Wake Up이라 통지 없이도 작동되긴 한다.(스레드 실행 순서를 조정할 경우) ==> 이 코드에서 안쓰면 데드락 발생함;
	// 다만 스레드 실행 순서가 꼬이면 Lost Wake Up으로 인해 데드락 발생
	
	// predicate 함수안의 조건이 true가 될 때 까지 대기한다.
	// predicate 없이 사용하는 경우도 있는데 이 경우 lock을 바로 점유한다.
	// 단일 wait만 사용하는 경우, 반드시 통지가 필요하다.

	
	// predicate - false : unlock() 후 대기
	// predicate - true :  lock 점유 유지 및 코드를 이어 수행
		
	Task();
	printf("[\033[33mReceiver\033[0m] : Job Finished.\n");
	
	printf(t_set t_color_g "[%s]" t_reset t_set t_color_r " UL UnLocked.\n" t_reset, ss.str().c_str());
}


int main()
{
	thread t[3];

	t[0] = thread(Consumer);
	t[1] = thread(Consumer);
	t[2] = thread(Producer);
	

	for (auto& i : t)
	{
		i.join();
	}
}