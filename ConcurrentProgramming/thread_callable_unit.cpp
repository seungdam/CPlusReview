#include "pch.h"

using namespace std;


// *** callable units \
\
	 callable unit 이란 함수처럼 동작하는 개체(Entity)들을 의미한다. \
	Thread(스레드)란, 본디 프로세스를 독립적으로 처리하는 작업 단위라고 정의할 수 있는데, \
	Callable Unit이 이 작업 단위에 해당한다.

// Callable Unit을 정의하는데는 다음 3가지 방법이 있다. \
\
1. Class 호출 형태 \
2. 함수 호출 형태 \
3. 람다 함수 호출 형태 
 
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
		 생성한 스레드가 작업을 완료할 때까지 기다린다.


		// 2. Detach   \
		// \
		 생성한 스레드 객체를 주 스레드와 분리한다. \
		하지만 main thread가 종료되면 해당 스레드도 종료된다. \
		이렇게 부모 스레드로 부터 분리된 자식 스레드를 Demon Process(Thread)라고 하기도 한다.
	
		//  *** thread가 joinable 하다. --> join, detach를 호출하지 않은 스레드라는 뜻. 
		// \
			join, detach를 호출하지 않은 스레드의 경우, 소멸자에서 std::terminate 함수를 호출하기 때문에, \
			예외 처리가 발생한다. 꼭 join 또는 detach함수를 호출해야한다.
		
		
		if (t[i].joinable()) t[i].join();
	}

}