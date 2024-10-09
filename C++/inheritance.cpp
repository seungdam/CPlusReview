#include "pch.h"

class Basic
{

public:

};

// ======= 클래스간의 관계 =======

// 상속
// Is - A Relationship
// derived is a basic 
class Derived : Basic
{

public:
};

// 의존
// Uses - A Relationship
// Car 클래스는 Gas 클래스에 의존적임. Gas 클래스가 변함에 따라 본인도 변경되야 함.

class Gas
{
};

class Car
{
	Gas a;
public:
	void UseGas() { /*...*/ };
};


// 연관

// Has - A Relationship (집합) 
// 하나의 클래스가 다른 클래스의 집합으로 구성됨.

class Engineer
{
};

class Factory
{
	Engineer emp[5];
};

// Owns - A Relationship (구성)
// 하나의 클래스가 다른 클래스를 구성하는 경우

class Bolt
{
};

class Machine
{
	Bolt part[100];
};

// C++의 interface ==> abstract class
// 추상 클래스는 오직 상속 목적으로써 활용된다.


class Base
{
	int a;
public:
	virtual void print() { std::cout << "Base\n"; }
};

class Child : public Base
{
public:
	void print() override { std::cout << "Child\n" ; }
};

class GrandChild final  : public Child
{
public:
	void print() override final  { std::cout << "GrandChild\n"; }
};

void print_class(Base& b)
{
	b.print();
}

class Test
{
public:
	virtual void func() = 0;
	virtual ~Test() = 0;
};

class CTest : public Test
{
	void func() { std::cout << "func().\n"; }
	~CTest() { std::cout << "Des\n."; }
};


int main()
{
	Base b;
	Child c;
	GrandChild gc;
	print_class(b);
	print_class(c);
	print_class(gc);


	Test* t = new CTest();
	t->func();
	delete t;
}