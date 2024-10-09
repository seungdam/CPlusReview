#include "pch.h"

class Basic
{

public:

};

// ======= Ŭ�������� ���� =======

// ���
// Is - A Relationship
// derived is a basic 
class Derived : Basic
{

public:
};

// ����
// Uses - A Relationship
// Car Ŭ������ Gas Ŭ������ ��������. Gas Ŭ������ ���Կ� ���� ���ε� ����Ǿ� ��.

class Gas
{
};

class Car
{
	Gas a;
public:
	void UseGas() { /*...*/ };
};


// ����

// Has - A Relationship (����) 
// �ϳ��� Ŭ������ �ٸ� Ŭ������ �������� ������.

class Engineer
{
};

class Factory
{
	Engineer emp[5];
};

// Owns - A Relationship (����)
// �ϳ��� Ŭ������ �ٸ� Ŭ������ �����ϴ� ���

class Bolt
{
};

class Machine
{
	Bolt part[100];
};

// C++�� interface ==> abstract class
// �߻� Ŭ������ ���� ��� �������ν� Ȱ��ȴ�.


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