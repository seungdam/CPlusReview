#include "pch.h"

using namespace std;

class Test
{
public:
	Test() {};
	~Test() {};
};

// NULL VS nullptr

// Null : 과거에 사용했던 것으로 정수값 0을 나타냄
// nullptr: 오직 null 포인터를 위한 것으로 어떤 포인터로도 캐스팅이 가능하지만, 정수로는 캐스팅이 안됨.

// 특정 컴파일러에 따라 NULL을 사용할 경우, 에러가 발생할 수 있음. clang, g++ 

void func(void* vptr)
{
	cout << "vptr\n";
}

void func(int null)
{
	cout << null;
}


int main()
{
	__int32 old_a(8);
	__int32 old_b = 7.7; // legal
	__int32 new_a{ 8 };
	//  int new_b { 7.7} // illegal

	vector<__int32> old_v(4); // 0,0,0,0
	vector<__int32> old_v2(4, 2); // 2,2,2,2
	vector<__int32> new_v{4}; // 0,0,0,0
	vector<__int32> new_v2{4, 2}; // 2,2,2,2

	
	Test t1(); // compiler hard to distinguish between function declaration and default constructor
	Test t2{}; // more easily distinguish
	
	func(nullptr); // vptr
	func(NULL); // 0
}