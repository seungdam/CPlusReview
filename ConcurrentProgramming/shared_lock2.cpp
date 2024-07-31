#include "pch.h"
#include <shared_mutex>
#include <unordered_map>
#include <sstream>
#include <random>

// 2024-07-30

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution uid(0, 30);
uniform_int_distribution uid2(1900, 1999);

shared_timed_mutex stm;
shared_mutex sm;

unordered_map<string, int32> dataset{ {"OHSD",2000}, {"KIMSN",1999}, {"PARKBS",1997} ,{"KIMSY",1934} };

string s[5]{ "OHSD","KIMSN","PARKBS","KIMSY","KANGHS"};

void Writer(string& key)
{
	stringstream ss;
	ss << std::this_thread::get_id();
	int32 id = std::stoull(ss.str());


	unique_lock<shared_timed_mutex> ul(stm);
	printf("[\033[32m%5d|\033[33mWriter\033[0m]\033[1;5;31m Now Updating...\033[0m\n", id);
	dataset[key] = uid2(dre);
	this_thread::sleep_for(3s);

	printf("[\033[32m%5d|\033[33mWriter\033[0m] Update Ended...\n", id);
	
	printf("\n	[\033[105m=== New Data Set ===\033[0m\n");
	for (auto& i : dataset)
	{
		printf("	   [\033[103;34m%6s|\033[0;36m%d\033[0m] \n", i.first.c_str(), i.second);
	}
}

void Reader(const string& key)
{
	stringstream ss;
	ss << std::this_thread::get_id();
	int32 id = std::stoull(ss.str());

	this_thread::sleep_for(std::chrono::seconds(uid(dre)));
	shared_lock<shared_timed_mutex> ul(stm);
	
	auto item = dataset.find(key);
	if (item != dataset.end())
	{
		printf("[\033[1;32m%5d|\033[1;36mReader\033[0m] Data Founded: [\033[103;34m%6s\033[0m]\033[36m %d\033[0m\n", id, item->first.c_str(), item->second);
	}
	else
	{
		printf("	\033[1;31m Data Not Found:\033[0m %6s\n", key.c_str());
	}
}

int main()
{
	thread w[20];
	thread r[30];

	for (auto& i : w)
	{
		i = thread(Writer, ref(s[uid(dre) % 4]));
	}

	for (auto& i : r)
	{
		i = thread(Reader, ref(s[uid(dre) % 4]));
	}


	for (auto& i : w)
	{
		i.join();
	}

	for (auto& i : r)
	{
		i.join();
	}
}