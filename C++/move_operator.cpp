#include "pch.h"

using namespace std;
// 이동 생성자 & 이동 할당 연산자

// 1. 복새 생성, 복사 할당, 소멸자가 있는 경우. synthesize하지 않는다.
// 2. 이동 함수가 정의되지 않았을 때, 자신의 member가 built-in type 혹은 이동연산자가 구현된 클래스일 경우 synthesize된다.
// 3. static member는 모든 클래스에 공유되기 때문에 이동되지 않는다.
// 4. 이동 함수를 구현할 경우 복사 함수들은 delete 처리되기 때문에 직접 구현해주어야 한다.

class Component {};

class Object
{
	int data{ 100 };
	Component c;

public:
	Object() = default;
	Object(const Object& rhs) : data(rhs.data), c(rhs.c) { cout << "Copy 생성\n"; }
	Object(Object&& rhs) noexcept : data(rhs.data), c(std::move(rhs.c))  { cout << "Move 생성\n"; }
	// rvalue ref에 const가 붙지 않았다. 왜? arg는 지금 객체로 이동(수정)될 객체이기 때문에 const를 붙일 필요 X

	// noexcept keyword: 
	// 1. move 연산은 반드시 데이터의 이동만 수행해야함. 
	// 2. 새로운 리소스 할당 혹은 예외(데이터가 일부만 이동하는 경우)가 발생할 수 있는 처리를 절대 수행해선 X
	// 3. 컨테이너에 해당 객체를 할당하기 위해선 이동 생성자가 noexcept문으로 구현되어야 한다.

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



// 상속 관계에서의 이동연산자 구현
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