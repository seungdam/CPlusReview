#include "pch.h"

using namespace std;
// �̵� ������ & �̵� �Ҵ� ������

// 1. ���� ����, ���� �Ҵ�, �Ҹ��ڰ� �ִ� ���. synthesize���� �ʴ´�.
// 2. �̵� �Լ��� ���ǵ��� �ʾ��� ��, �ڽ��� member�� built-in type Ȥ�� �̵������ڰ� ������ Ŭ������ ��� synthesize�ȴ�.
// 3. static member�� ��� Ŭ������ �����Ǳ� ������ �̵����� �ʴ´�.
// 4. �̵� �Լ��� ������ ��� ���� �Լ����� delete ó���Ǳ� ������ ���� �������־�� �Ѵ�.

class Component {};

class Object
{
	int data{ 100 };
	Component c;

public:
	Object() = default;
	Object(const Object& rhs) : data(rhs.data), c(rhs.c) { cout << "Copy ����\n"; }
	Object(Object&& rhs) noexcept : data(rhs.data), c(std::move(rhs.c))  { cout << "Move ����\n"; }
	// rvalue ref�� const�� ���� �ʾҴ�. ��? arg�� ���� ��ü�� �̵�(����)�� ��ü�̱� ������ const�� ���� �ʿ� X

	// noexcept keyword: 
	// 1. move ������ �ݵ�� �������� �̵��� �����ؾ���. 
	// 2. ���ο� ���ҽ� �Ҵ� Ȥ�� ����(�����Ͱ� �Ϻθ� �̵��ϴ� ���)�� �߻��� �� �ִ� ó���� ���� �����ؼ� X
	// 3. �����̳ʿ� �ش� ��ü�� �Ҵ��ϱ� ���ؼ� �̵� �����ڰ� noexcept������ �����Ǿ�� �Ѵ�.

	Object& operator=(const Object& rhs) 
	{ 
		cout << "Copy Assgin\n"; 
		if (this != &rhs) // self-assignment check
		{
			c = rhs.c;
			data = rhs.data;
		}
		return *this;
	}
	Object& operator=(Object&& rhs) noexcept
	{ 
		cout << "Move Assign\n";
		if (this != &rhs)
		{
			data = rhs.data;
			c = move(rhs.c);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Object& obj) { os << obj.data; return os; }
};



// ��� ���迡���� �̵������� ����
class Base
{
	int32 bdata{ 100 };
	int32 mid{ 0 };
	static int32 id;
public:
	Base() = default;
	Base(const int& data) : bdata(data), mid(id++) {  }
	Base(const Base& rhs) : bdata(rhs.bdata), mid(rhs.id) {  }
	Base(Base&& rhs) noexcept : bdata(rhs.bdata), mid(rhs.id) { cout << "Base Move\n"; }

	Base& operator=(const Base& rhs) 
	{
		if (this != &rhs) 
		{
			bdata = rhs.bdata;
			mid = rhs.id;
		}
		return *this;
	}
	Base& operator=(Base&& rhs) noexcept 
	{
		if (this != &rhs)
		{
			bdata = rhs.bdata;
			mid = rhs.mid;
		}
		return *this;
	}

	int getId() const { return mid; }
	int getData() const { return bdata; }
};

int32 Base::id{ 0 };

class Derived : public Base
{
	Component c;
public:
	Derived() = default;
	Derived(const int& data) : Base(data) {}
	Derived(const Derived& rhs) : Base(rhs), c(rhs.c) { cout << "Derived Copy\n"; }
	Derived(Derived&& rhs) noexcept : Base(std::move(rhs)), c(std::move(rhs.c)) 
	{ 
		cout << "Derived Move\n"; 
	}

	Derived& operator=(const Derived& rhs)
	{
		cout << "Derived Copy\n";
		if (this != &rhs)
		{
			c = rhs.c;
		}
		return *this;
	}
	Derived& operator=(Derived&& rhs) noexcept
	{

		cout << "[" << rhs.getId() << "] Derived Move to [" << Base::getId() << "] Derived Class\n";
		if (this != &rhs)
		{
			Base::operator=(move(rhs));
			c = move(rhs.c);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Derived& rhs)
	{
		os << "[" << rhs.getId() << "] " << rhs.getData();
		return os;
	}
};


int main()
{

	Object obj;
	Object obj2{ obj }; // Copy Constructor
	Object obj3 = obj; // Copy Constructor Elison.. call default constructor


	cout << "\n\n";
	Object mobj1 = Object{}; // Move Construtor
	Object mobj2 = std::move(obj); // Move Elison
	Object mobj3{ std::move(obj2) }; // Move Constructor
	mobj2 = Object(); // Move Assginment
	
	cout << "\n\n";
	Derived d{ 100 }; // 0 
	Derived d2{ 20 }; // 1

	d2 = Derived{ 200 }; //2
	cout << d2 << "\n";

	String s{ std::move(String("Hello"))};
}