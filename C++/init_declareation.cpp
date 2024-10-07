#include "pch.h"

using namespace std;

class Test
{
public:
	Test() {};
	~Test() {};
};

// NULL VS nullptr

// Null : ���ſ� ����ߴ� ������ ������ 0�� ��Ÿ��
// nullptr: ���� null �����͸� ���� ������ � �����ͷε� ĳ������ ����������, �����δ� ĳ������ �ȵ�.

// Ư�� �����Ϸ��� ���� NULL�� ����� ���, ������ �߻��� �� ����. clang, g++ 

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