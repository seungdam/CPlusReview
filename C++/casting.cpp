#include <iostream>

using namespace std;

// c - syntax
// (Type)expr

// current syntax
// xyz_cast<Type>(expr)
// -static_cast: 다른 타입으로 형변환 할 때 사용
// -const_cast: const - non-const 타입 간의 형변환 과정에서 사용
// -reinterpret_cast: data를 정의되지 않은 바이너리 타입으로 buffer에 저장하기 위함. low-level에서 활용
// -dynamic_cast: 하위 클래스의 포인터를 상위 클래스의 포인터로 형변환. (런타임 중에 수행된다.)

class CBase
{
	int base_data;
public:
	CBase() : base_data(0) { cout << "CBase Constructor\n"; }
	CBase(const int& data) : base_data(data) { cout << "CBase Constructor\n"; }
	~CBase() { cout << "CBase Destory\n"; }

	virtual void Display() { cout << "Data:" << base_data << "\n"; }
};

class CDerived : public CBase
{
	int derived_data = 0;
public:
	CDerived() : CBase(), derived_data(10) { cout << "CDerived Constructor\n"; }
	~CDerived() { cout << "CDerived Destory\n"; }

	virtual void Display() override { cout << "Data " << derived_data << "\n"; }
};

int main()
{
	CBase* base = new CDerived{};

	CDerived derived{};
	base->Display();
	CBase cbase = static_cast<CBase>(derived);
	
	CDerived* cderived = dynamic_cast<CDerived*>(&cbase);
	cderived->Display();
}