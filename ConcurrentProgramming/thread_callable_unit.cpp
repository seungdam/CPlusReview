#include "pch.h"

using namespace std;


// *** callable units \
\
	 callable unit �̶� �Լ�ó�� �����ϴ� ��ü(Entity)���� �ǹ��Ѵ�. \
	Thread(������)��, ���� ���μ����� ���������� ó���ϴ� �۾� ������� ������ �� �ִµ�, \
	Callable Unit�� �� �۾� ������ �ش��Ѵ�.

// Callable Unit�� �����ϴµ��� ���� 3���� ����� �ִ�. \
\
1. Class ȣ�� ���� \
2. �Լ� ȣ�� ���� \
3. ���� �Լ� ȣ�� ���� 
 
class CallableObject
{
public:
	void operator()()
	{
		cout << "Callable Object. ==> Callable Unit\n";
	}
};


void CallableFunc()
{
	cout << "Callable Function. ==> Callable Unit\n";
}


int main()
{
	thread t[3];
	t[0] = thread(CallableFunc);
	t[1] = thread(CallableObject());
	t[2] = thread([]() {cout << "Callable Lamda Function. ==> Callable Unit\n"; });

	for (int i = 0; i < 3; ++i)
	{
		// *** Thread's Life Cycle

		// 1. Join \
		// \
		 ������ �����尡 �۾��� �Ϸ��� ������ ��ٸ���.


		// 2. Detach   \
		// \
		 ������ ������ ��ü�� �� ������� �и��Ѵ�. \
		������ main thread�� ����Ǹ� �ش� �����嵵 ����ȴ�. \
		�̷��� �θ� ������� ���� �и��� �ڽ� �����带 Demon Process(Thread)��� �ϱ⵵ �Ѵ�.
	
		//  *** thread�� joinable �ϴ�. --> join, detach�� ȣ������ ���� �������� ��. 
		// \
			join, detach�� ȣ������ ���� �������� ���, �Ҹ��ڿ��� std::terminate �Լ��� ȣ���ϱ� ������, \
			���� ó���� �߻��Ѵ�. �� join �Ǵ� detach�Լ��� ȣ���ؾ��Ѵ�.
		
		
		if (t[i].joinable()) t[i].join();
	}

}