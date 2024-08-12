#include "pch.h"
#include <sstream>

using namespace std;

void NonInterruptibleWorker()
{
	int32 count(0);
	std::stringstream ss;
	ss << std::this_thread::get_id();
	uint64_t tid = std::stoull(ss.str());

	while (10 > count)
	{
		
		printf(t_set t_bold t_g "[%lld]"
			t_set t_bold t_y " Still Working... %d\n" t_reset, tid, count);
		this_thread::sleep_for(0.5s);
		++count;
	}

	printf(t_set t_bold t_g "[%lld]"
		t_set t_bold t_c " Job Finished...\n" t_reset, tid);
}

void InterruptibleWorker(stop_token stoken)
{
	int32 count(0);
	std::stringstream ss;
	ss << std::this_thread::get_id();
	uint64_t tid = std::stoull(ss.str());

	while (10 > count )
	{
		
		if (stoken.stop_requested())
		{
			printf(t_set t_g "[%lld]"
				t_set t_bold t_r " Stop Requested\n",tid);
			return;
		}

		printf( t_set t_g "[%lld]"
				t_set t_bold t_y " Still Working... " t_reset
				t_set t_bold t_p  "& Stoken is possible: " t_reset "%s\n", 
				tid, 
				stoken.stop_possible() ? "True" : "False");
		this_thread::sleep_for(0.5s);
		++count;
	}

	printf(t_set t_bold t_g "[%lld]"
		t_set t_bold t_c " Job Finished... %d\n" t_reset, tid,count);
}

int main()
{
	jthread jthr([] 
			{ 
			printf(t_set t_y "Joining Thread" t_set t_c " (C++20)\n" t_reset); 
			this_thread::sleep_for(5s);
			});
	// *** C++20 부터 지원하는 joining thread
	// RAII 기능 및 확장된 인터페이스를 제공하는 특징을 지님.
	// 소멸자에서 join()을 호출한다.
	// join()을 호출하지 않아도 program이 terminate 되지 않는다.

	// jthread는 멤버 변수로 std::stop_resource라는 친구를 가지는데, 이를 활용해
	// 스레드 동작을 제어할 수 있음. Interrupt 발생 가능

	// 


	// 소멸자에서 join을 호출하기 때문에 main 스레드 진행 동안에는 True를 리턴한다.
	printf( t_set t_y "jthr.joinable: " 
			t_set t_p "%s\n", (jthr.joinable() ? "(True)" : "(False)"));

	jthread it(InterruptibleWorker);
	// 여기 보면 stop_token을 명시적으로 전달하지 않음에도 불구하고, 코드에 문제가 없다.
	// 그 이유는 jthread에선 넘겨진 callable_unit에게 stop_source::get_stop_token을 내부적으로 호출해 넘겨주기 때문이다.

	jthread nit(NonInterruptibleWorker);
	
	this_thread::sleep_for(1s);

	nit.request_stop(); // No Effect
	it.request_stop(); // Yes Effect

	// jthread::request_stop() ==> private member인 stop_resource의 request_stop 호출

}