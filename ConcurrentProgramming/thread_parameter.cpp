#include "pch.h"

using namespace std;

void TaskCopy(int32 param)
{
	cout << "copy param :" << param << "\n";
}

void TaskRef(int32& lparam, int32&& rparam)
{
	cout << "l-ref param: " << lparam++   << "\n";
	cout << "r-ref param: " << rparam  << "\n";

}

template<typename... Tys> // template-parameter pack
void TaskVArg(Tys&&... params)
{
	cout << "varg param: ";
	(cout << ... << params); // fold expression <== C++17부터 제공함.
	cout << "\n";
}

int main()
{
	int32 a = 0;
	int32 b = 0;

	// *** thread의 인자 \
	\
	 thread는 기본적으로 인자를 "복사" 형태로 받아들이며, r/lvalue ref, 이동의 형태로 값을 받는 것또한 가능하다. \
	이때 ref의 형태로 인자를 주는 경우, ref 형태로 암시적 형변환이 수행되지 않기 때문에 주의해야한다. \
	또한 rvalue 참조에 관해 perfect forwarding을 제공한다고 한다. 

	thread copy_thread(TaskCopy, a);
	copy_thread.join();

	thread ref_thread(TaskRef, std::ref(a), std::move(b));
	ref_thread.join();
	
	cout << "a: " << a << "\n"; // 1
	cout << "b: " << b << "\n"; // 0

	// 일반적인 탬플릿 사용 경우와 달리 가변 인자 탬플릿을 사용하는 함수를 callable unit으로 넘겨주어야 할 경우, \
	가변인자에 관한 탬플릿 타입들을 명시해주어야 한다.
	thread varg_thread(TaskVArg<int32, int32, int32, int32, string>, 1, 2, 3, 4, "hello");
	varg_thread.join();
	
	TaskVArg(1, 2, 3, 4, "hello"); 
	
	
}