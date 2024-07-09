#include "pch.h"

class Interface abstract
{
	virtual void Func()  = 0; // ���� ���� �Լ�(= �߻��Լ�)�� ����
	virtual void Func2() = 0;
	virtual void Func3() = 0;
};

// *** class vs struct
// ��� �� �� ��� ������ ����� ����
// struct ==> POD�� ǥ���� �� ����ϴ� ���� �̻���

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
	// b.name = "Button";  ==> NO ������ ���� �߻� 
	// b.IsEqual(b2);  ==> NO ������ ���� �߻�

	// Why?
	// Rectangle�� Circle�� name �� ��� ���� �����ؾ��ϴ� �� ��
	// Rectangle�� Circle�� IsEqual �� ��� ���� ȣ���� �� ���� X
	// �� ��ȣ�ϴ�.

	
	// �ذ���
	// 1. name ��� ������ ���� ����
	// ���� �⺻ Ŭ���� ���·� ����� ��������. public Object ==> virtual public Object
	// �� ���� �⺻ Ŭ������ ��ü�� constexpr �����ڸ� ������ �� X
	b.name = "Button";
	
	// 2. ��� ��ų �Լ��� ���� ������ ������ �� �ִ�.
	// Ex) Rectangle::IsEqual() ���� ���(����ȭ ȣ��)���� ȣ��
	std::cout << std::boolalpha << b.IsEqual(b) << "\n";
	std::cout<< std::boolalpha  << b.IsEqual(b2);


}
