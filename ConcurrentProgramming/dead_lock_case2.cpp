#include "pch.h"

using namespace std;

struct Locker
{
	string name;
	mutex m;
};

void DeadlyEmbrace(Locker& l1, Locker& l2)
{
	l1.m.lock();
	std::cout << "\033[32m[" << this_thread::get_id() << "|" << l1.name << "]\033[0m" << "Get First Lock\n";
	l2.m.lock();
	std::cout << "\033[33m[" << l2.name << "]\033[0m" << "Get Second Lock\n";
	std::cout << "Do Tasking\n";

	l1.m.unlock();
	l2.m.unlock();
}

int main()
{
	Locker l1;
	l1.name = "L1";
	Locker l2;
	l2.name = "L2";

	thread t[3];
	t[0] = thread(DeadlyEmbrace, ref(l1), ref(l2));
	t[1] = thread(DeadlyEmbrace, ref(l2), ref(l1));
	t[2] = thread([&]() { DeadlyEmbrace(l1, l2); });
	t[0].join();
	t[1].join();
	t[2].join();


}