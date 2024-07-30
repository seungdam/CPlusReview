#include "pch.h"

using namespace std;

struct SharedData
{
	string s;
	mutex m;
};

void DeadlyEmbrace(SharedData& l1, SharedData& l2)
{
	l1.m.lock();
	std::cout << "\033[32m[" << this_thread::get_id() << "|" << l1.s << "]\033[0m" << "Get First Lock\n";
	l2.m.lock();
	std::cout << "\033[33m[" << l2.s << "]\033[0m" << "Get Second Lock\n";
	std::cout << "Do Tasking\n";

	l1.m.unlock();
	l2.m.unlock();
}

int main()
{
	SharedData l1;
	l1.s = "L1";
	SharedData l2;
	l2.s = "L2";

	thread t[2];
	t[0] = thread(DeadlyEmbrace, ref(l1), ref(l2));
	t[1] = thread(DeadlyEmbrace, ref(l2), ref(l1));

	t[0].join();
	t[1].join();


}