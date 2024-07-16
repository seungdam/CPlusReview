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
	scoped_thread(scoped_thread& sc) = delete; // 복사생성 불가
	scoped_thread& operator=(scoped_thread& rhs) = delete; // 대입 불가
};

int main()
{
	thread t[3];
	t[0] = thread(CallableFunc);
	t[1] = thread(CallableObject());
	t[2] = thread([]() {cout << "Callable Lamda Function. ==> Callable Unit\n"; });

	for (int i = 0; i < 3; ++i)
	{

		// *** thread가 joinable 하다. --> join, detach를 호출하지 않은 스레드라는 뜻.
		// join, detach를 호출하지 않은 스레드의 경우, 소멸자에서 thread::terminate 함수를 호출하기 때문에,
		// 예외 처리가 발생한다. 꼭 join 또는 detach함수를 호출해야한다.
		if (t[i].joinable()) t[i].join();
	}

	// *** scoped_thread
	// 항상 스레드의 라이프 사이클을 주시해야한다는 것은 매우 귀찮은 행위.
	// 그렇다면 thread를 wrapping하는 객체를 정의해 join을 알아서 수행할 수 있도록 하는건 어떠한가?
	// 라는 아이디어에서 나온 앤서니 윌리엄스의 scoped_thread

	scoped_thread st(thread([]() {cout << "Scoped Thread\n"; }));

	int a = 100;
	reference_wrapper<__int32> rw(a);
	thread t3(RefCallableFunc, rw);
	t3.join();
}