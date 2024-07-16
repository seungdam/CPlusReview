#include "pch.h"

using namespace std;
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

void RefCallableFunc(__int32& parameter)
{
	cout << "Ref " << parameter << "\n";
}


class scoped_thread
{
	thread t;
public:
	explicit scoped_thread(thread input_thread) : t(move(input_thread))
	{
		if (!t.joinable()) throw logic_error("Unable Thread\n");
	}
	~scoped_thread() 
	{ 
		t.join(); 
	}
	scoped_thread(scoped_thread& sc) = delete; // ������� �Ұ�
	scoped_thread& operator=(scoped_thread& rhs) = delete; // ���� �Ұ�
};

int main()
{
	thread t[3];
	t[0] = thread(CallableFunc);
	t[1] = thread(CallableObject());
	t[2] = thread([]() {cout << "Callable Lamda Function. ==> Callable Unit\n"; });

	for (int i = 0; i < 3; ++i)
	{

		// *** thread�� joinable �ϴ�. --> join, detach�� ȣ������ ���� �������� ��.
		// join, detach�� ȣ������ ���� �������� ���, �Ҹ��ڿ��� thread::terminate �Լ��� ȣ���ϱ� ������,
		// ���� ó���� �߻��Ѵ�. �� join �Ǵ� detach�Լ��� ȣ���ؾ��Ѵ�.
		if (t[i].joinable()) t[i].join();
	}

	// *** scoped_thread
	// �׻� �������� ������ ����Ŭ�� �ֽ��ؾ��Ѵٴ� ���� �ſ� ������ ����.
	// �׷��ٸ� thread�� wrapping�ϴ� ��ü�� ������ join�� �˾Ƽ� ������ �� �ֵ��� �ϴ°� ��Ѱ�?
	// ��� ���̵��� ���� �ؼ��� ���������� scoped_thread

	scoped_thread st(thread([]() {cout << "Scoped Thread\n"; }));

	int a = 100;
	reference_wrapper<__int32> rw(a);
	thread t3(RefCallableFunc, rw);
	t3.join();
}