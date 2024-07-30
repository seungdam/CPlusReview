#include "pch.h"
#include <shared_mutex>
#include <random>
#include <sstream>
#include <unordered_map>

using namespace std;
// *** shared_lock
// reader-writer lock¿ª ¿ß«— RAII Wrapper class

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution uid(1, 10);

shared_timed_mutex stm;
shared_mutex sm;


string s = "Count Value:  ";

void Writer()
{
	static int32 cnt = 0;
	char ccnt[2];
	
	stringstream ss;
	ss << std::this_thread::get_id();
	int32 id = std::stoull(ss.str());

	while (cnt < 10)
	{
		unique_lock<shared_timed_mutex> ul(stm);
		printf("[\033[32m%5d|\033[33mWriter\033[0m]\033[31m Now Updating...\033[0m\n", id);
		::_itoa_s(cnt++, ccnt, _countof(ccnt), 10);
		s.pop_back();
		s.append(ccnt);
		this_thread::sleep_for(2s);
		printf("[\033[32m%5d|\033[33mWriter\033[0m] Updating Ended...\n", id);
	}

	printf("[\033[32m%5d|\033[33mWriter\033[0m] Job Finished\n", id);
}

void Reader()
{
	stringstream ss;
	ss << std::this_thread::get_id();
	int32 id = std::stoull(ss.str());

	this_thread::sleep_for(std::chrono::seconds(uid(dre)));
	shared_lock<shared_timed_mutex> ul(stm);
	printf("	[\033[32m%5d|\033[34mReader\033[0m]\033[36m %s\033[0m\n", id, s.c_str());
}


int main()
{
	thread w(Writer);
	thread r[100];

	for (auto& i : r)
	{
		i = thread(Reader);
	}

	w.join();

	for (auto& i : r)
	{
		i.join();
	}
}
