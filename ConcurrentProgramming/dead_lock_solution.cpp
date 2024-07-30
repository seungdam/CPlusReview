#include "pch.h"

using namespace std;

struct Locker
{
	mutex m;
	string name;
};

// Solve the deadly embrace problem
void SolveDeadlyEmbrace(Locker& l1, Locker& l2)
{	
	
	unique_lock<mutex> ul1(l1.m, defer_lock); // l1�� mutex�� �����ϵ�, �̹� lock�� �� �������� �˷���.
	std::cout << "\033[32m[" << this_thread::get_id() << "|\033[33m" << l1.name << "]\033[0m" << " Get First Lock\n";
	
	this_thread::sleep_for(1ms);
	unique_lock<mutex> ul2(l2.m, defer_lock);
	std::cout << "\033[32m[" << this_thread::get_id() << "|\033[33m" << l2.name << "]\033[0m" << " Get Second Lock\n";
	
	 // l1,l2�� ���� ���ÿ� ����� ����.
	// std::lock & std::scoped_lock(C++17)�� ����ؼ� �� �� �̻��� mutex�� atomic�ϰ� Lock�� �� �ִ�.
	// lock(ul1,ul2);
	scoped_lock sl(ul1, ul2);
	std::cout << "\033[32m[" << this_thread::get_id() << "]\033[0m" << "\033[31m"<< " Do Tasking"<< "\033[0m\n";
}

void SolveDeadlyEmbrace2(Locker& l1, Locker& l2)
{
	scoped_lock(l1.m , l2.m); // lock ���ٴ� scoped lock�� �� ����
	std::cout << "\033[32m[" << this_thread::get_id() << "|\033[33m" << l1.name << "]\033[0m" << " Get First Lock\n";
	std::cout << "\033[32m[" << this_thread::get_id() << "|\033[33m" << l2.name << "]\033[0m" << " Get Second Lock\n";
	std::cout << "\033[32m[" << this_thread::get_id() << "]\033[0m" << "\033[31m" << " Do Tasking" << "\033[0m\n";
}

int32 main()
{
	Locker l1;
	l1.name = "Locker-1";
	Locker l2;
	l2.name = "Locker-2";

	thread t[2];
	t[0] = thread([&] {SolveDeadlyEmbrace2(l1, l2); });
	t[1] = thread([&] {SolveDeadlyEmbrace2(l2, l1);});

	t[0].join();
	t[1].join();

}