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

int main()
{

}