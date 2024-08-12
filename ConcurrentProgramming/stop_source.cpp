#include "pch.h"
#include <sstream>
#include <random>



std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 5);

using namespace std;

thread_local int32 cnt(0);

void Worker(std::stop_token stoken)
{
	
	this_thread::sleep_for(3s);
	
	stringstream ss;
	ss << this_thread::get_id();
	uint64 tid = stoull(ss.str());
	dre.seed(rd());
	while (true)
	{
		this_thread::sleep_for(chrono::seconds(uid(dre)));
		if (stoken.stop_requested())
		{
			printf( t_set t_bold t_g  "[%08lld] "
					t_set t_bold t_r  "Task Terminated..\n" t_reset, tid);
			break;
		}
		printf(t_set t_bold t_g  "[%08lld] "
		 t_set t_bold t_y  "Do Tasking..." 
		 t_set t_bold t_p "[%d]\n" t_reset, tid, cnt++);
	}

	printf(t_set t_bold t_g  "[%08lld] "
		t_set t_bold t_y  "Total Count: "
		t_set t_bold t_p "[%d]\n" t_reset, tid, cnt);
}

void Worker2()
{
	return;
}

int main()
{
	stop_source ssource;
	auto stoken = ssource.get_token();
	vector<jthread> workers;

	for(int32 i = 0; i < 5; ++i)
	{
		workers.push_back(jthread(Worker, ssource.get_token()));
	}

	printf("=============stop_source==========\n");
	printf(t_set t_y  "ssource.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, ssource.stop_requested() ? " True" : "False");
	printf(t_set t_y  "stoken.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, stoken.stop_requested() ? " True" : "False");
	

	this_thread::sleep_for(5s);
	ssource.request_stop();
	for (auto& i : workers) i.join();
	
	
	printf(t_set t_y  "ssource.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, ssource.stop_requested() ? " True" : "False");
	printf(t_set t_y  "stoken.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, stoken.stop_requested() ? " True" : "False");
	
	

	std::stop_source invalid_ssource(nostopstate); // 기본 생성자로 생성된 stop_source 객체는 유효하지 않음

	printf(t_set t_y  "invalid_ssource.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, stoken.stop_possible() ? " True" : "False");
	printf(t_set t_y  "invalid_stoken.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, stoken.stop_possible() ? " True" : "False");

}