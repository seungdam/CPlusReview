#include "pch.h"


// ��� ���迡�� virtual Ű���带 ���� ���ǵ� �Լ�����,
// �� �Լ� ���� ������ �����Լ����̺� ���� ������ ������ ������ �ִ� (8����Ʈ)
// �ش� �����Լ����̺� �����Ͱ� ����Ű�� �����Լ����̺� ���� �����Լ� �����Ϳ� ���ٿ�
// ��� �ܰ� �� ������ �Լ��� ȣ���� �� �ֵ��� �����ش�. �̰��� �������� �ش��Ѵ�.
// ���� �������̽��� ���� �پ��� ����� ������ �� �ִٴ� Ư¡�� �ִ�.
// �̷��� ���� �������̽��� ���� ���� �ٸ� ���Ǹ� �����ϴ� ���� �������̵��̶�� �Ѵ�.
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
	std::cout << sizeof(Basic) << " =  8(x64 ȯ���� ������ ũ��) + 4(��� ����) + 4(�е� ����Ʈ)\n";
	std::cout << sizeof(Derived) << " = 16(�θ� Ŭ���� ũ��)       + 4(��� ����) + 4(�е� ����Ʈ) \n";
	
}