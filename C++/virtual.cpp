#include "pch.h"


// 상속 관계에서 virtual 키워드를 통해 정의된 함수들은,
// 각 함수 별로 별도의 가상함수테이블에 관한 포인터 정보를 가지고 있다 (8바이트)
// 해당 가상함수테이블 포인터가 가르키는 가상함수테이블 안의 가상함수 포인터에 접근에
// 상속 단계 별 적절한 함수를 호출할 수 있도록 도와준다. 이것이 다형성에 해당한다.
// 단일 인터페이스에 관해 다양한 기능을 제공할 수 있다는 특징이 있다.
// 이렇게 단일 인터페이스에 관해 서로 다른 정의를 수행하는 것을 오버라이딩이라고 한다.
class Basic
{
	static int32 count;
	int32 a;
public:
	Basic() : a(0) { std::cout << "Basic Constructor\n"; ++count; }
	~Basic() { std::cout << "Basic Destructor\n"; }
	virtual void Func() { std::cout << "Basic Func\n"; }
};

class Derived : public Basic
{
	int32 b;
public:
	 Derived() : b(0) { std::cout << "Derived Constructor\n"; }
	~Derived() { std::cout << "Derived Destructor\n"; }
	void Func() override { std::cout << "Derived Func\n"; }
};

int32 Basic::count = 0;

int main()
{
	std::cout << "Call Inheritance Class Constructor\n";
	Basic* arr[]
	{
		new Basic(),
		new Derived(),
		
	};
	std::cout << "\n\nCall Override Function Result";
	for (auto i : arr)
	{
		i->Func();
	}
	std::cout << "\n\n Call Override Function By Reference";
	Basic& rb = *arr[1];
	rb.Func();
	std::cout << "\n\n Class Size";
	std::cout << sizeof(Basic) << " =  8(x64 환경의 포인터 크기) + 4(멤버 변수) + 4(패딩 바이트)\n";
	std::cout << sizeof(Derived) << " = 16(부모 클래스 크기)       + 4(멤버 변수) + 4(패딩 바이트) \n";
	
}