#include "pch.h"
#include <condition_variable>

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid(1, 2);
uniform_int_distribution<int> rgb(1, 230);

// shared_data
vector<int32> shared_data;
bool is_data_ready;

// for thread synchronize
mutex m;
condition_variable cv;




void Reciever() // reciver thread
{
	PrintThreadMsg(rgb(dre), "\033[1;33m[Recv]:\033[0m Waiting...\n");
	unique_lock<mutex> ul(m);
	cv.wait(ul, [] {return is_data_ready; });
	shared_data[1] = 0;
	PrintThreadMsg(rgb(dre), "\033[1;33m[Recv]:\033[0m Job Finished.\n");
}

void Sender() // sender thread
{
	shared_data = { 1,2,3 }; // data set
	{
		lock_guard<mutex> lg(m); // lock_guard를 사용해 mutex life cycle을 보장
		is_data_ready = true; //
		PrintThreadMsg(rgb(dre),"\033[1;33m[Send]:\033[0m Data is Ready.\n");
	}
	cv.notify_one(); // occur notification
}



int main()
{
	
	jthread t1(Reciever);
	jthread t2(Sender);
}