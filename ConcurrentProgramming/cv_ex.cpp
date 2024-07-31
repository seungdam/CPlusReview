#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

// shared_data
vector<__int32> shared_data;
bool is_data_ready;

// for thread synchronize
mutex m;
condition_variable cv;




void WaitingForWork() // reciver thread
{
	cout << "Reciver: Waiting.\n";
	unique_lock<mutex> ul(m);
	cv.wait(ul, [] {return is_data_ready; });
	/* notification �� �� ������ lock�� ������
	wait (lock, predicate())
	{
		while(!predicate())
		{
			wait(lock);
		}
	}
	*/
	shared_data[1] = 0;
	cout << "Reciver: Work Done.\n";
}

void SetDataReady() // sender thread
{
	shared_data = { 1,2,3 }; // data set
	{
		lock_guard<mutex> lg(m); // lock_guard�� ����� mutex life cycle�� ����
		is_data_ready = true; //
		std::cout << "Sender: Data Prepared.\n";
	}
	cv.notify_one(); // occur notification
}



int main()
{
	thread t1(WaitingForWork);
	thread t2(SetDataReady);

	t1.join();
	t2.join();
}