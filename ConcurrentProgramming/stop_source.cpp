#include "pch.h"
#include "logging.h"


std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 2);
std::uniform_int_distribution<int> rgb(1, 230);

using namespace std;





void Worker(std::stop_token stoken)
{

	stringstream ss;
	auto thr_color = rgb(dre);
	int32 cnt = 0;
	atomic<bool> flag = true;
	

	while (true)
	{
		this_thread::sleep_for(chrono::seconds(uid(dre)));
		PrintThreadMsg(thr_color, "\033[0mDo Tasking...[", cnt++, "]\033[0m\n");
		if (stoken.stop_requested())
		{
			break;
		}
	}
	PrintThreadMsg(thr_color, "\033[1;31m Task Terminated..\033[0m", " Total Count: [", cnt, "]\n");

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

	printf("====stop_source====\n");
	printf(t_set t_y  "ssource.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, ssource.stop_requested() ? " True" : "False");
	printf(t_set t_y  "stoken.stop_requested(): "
		t_set t_bold t_r	"%s\n\n" t_reset, stoken.stop_requested() ? " True" : "False");
	
	
	std::stop_source invalid_ssource(nostopstate);
	// *** nostopstate 옵션을 통해 생성한 ssource는 stop_possible()이 false를 return한다.
	printf("====invalid stop_source====\n");
	printf(t_set t_y  "invalid_ssource.stop_possible(): "
		t_set t_bold t_r	"%s\n" t_reset, invalid_ssource.stop_possible() ? " True" : "False");
	printf(t_set t_y  "invalid_stoken.stop_possible(): "
		t_set t_bold t_r	"%s\n\n" t_reset, invalid_ssource.get_token().stop_possible() ? " True" : "False");

	this_thread::sleep_for(10s);
	
	printf("\n\nCall Request Stop!!!\n");
	ssource.request_stop();

	printf(t_set t_y  "ssource.stop_requested(): "
		t_set t_bold t_r	"%s\n" t_reset, ssource.stop_requested() ? " True" : "False");
	printf(t_set t_y  "stoken.stop_requested(): "
		t_set t_bold t_r	"%s\n\n" t_reset, stoken.stop_requested() ? " True" : "False");


}