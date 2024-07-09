#include "pch.h"

class Interface abstract
{
	virtual void Func()  = 0; // 순수 가상 함수(= 추상함수)로 정의
	virtual void Func2() = 0;
	virtual void Func3() = 0;
};

// *** class vs struct
// 사실 상 둘 모두 동일한 기능을 지원
// struct ==> POD를 표현할 때 사용하는 것이 이상적

class Object
{
public:
	std::string name;
public:
	Object() {}
	Object(std::string s) : name(s) {}
	virtual bool IsEqual(const Object& other)
	{
		std::cout << "Object->IsEqual\n";
		return &other == this;
	}
};

class Rectangle : virtual public Object
{
public:
	Rectangle() : Object() {}
	~Rectangle() {}
	virtual bool IsEqual(const Rectangle& other) final
	{
		std::cout << "Rect->IsEqual\n";
		return &other == this;
	}
};

class Circle : virtual public Object
{
public:
	Circle() : Object() {}
	~Circle() {}
	 
	virtual bool IsEqual(const Circle& other)
	{
		std::cout << "Circle->IsEqual\n";
		return &other == this;
	}
};


class Button :  public Circle, public Rectangle
{
public:
	Button() : Circle(), Rectangle() {}

	virtual bool IsEqual(const Button& other) final
	{
		bool ok = (Rectangle::IsEqual(other) && Circle::IsEqual(other));
		return ok;
	}
};



int main()
{
	Button b;
	Button b2;
	// b.name = "Button";  ==> NO 컴파일 오류 발생 
	// b.IsEqual(b2);  ==> NO 컴파일 오류 발생

	// Why?
	// Rectangle과 Circle의 name 중 어느 것을 수정해야하는 지 모름
	// Rectangle과 Circle의 IsEqual 중 어느 것을 호출할 지 알지 X
	// 즉 모호하다.

	
	// 해결방안
	// 1. name 멤버 변수에 관한 문제
	// 가상 기본 클래스 형태로 상속을 수행하자. public Object ==> virtual public Object
	// 단 가상 기본 클래스의 주체는 constexpr 생성자를 선언할 수 X
	b.name = "Button";
	
	// 2. 상속 시킬 함수에 관해 별도로 지정할 수 있다.
	// Ex) Rectangle::IsEqual() 등의 방식(정규화 호출)으로 호출
	std::cout << std::boolalpha << b.IsEqual(b) << "\n";
	std::cout<< std::boolalpha  << b.IsEqual(b2);


}
