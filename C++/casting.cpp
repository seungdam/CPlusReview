#include <iostream>

using namespace std;

// c - syntax
// (Type)expr

// current syntax
// xyz_cast<Type>(expr)
// -static_cast: �ٸ� Ÿ������ ����ȯ �� �� ���
// -const_cast: const - non-const Ÿ�� ���� ����ȯ �������� ���
// -reinterpret_cast: data�� ���ǵ��� ���� ���̳ʸ� Ÿ������ buffer�� �����ϱ� ����. low-level���� Ȱ��
// -dynamic_cast: ���� Ŭ������ �����͸� ���� Ŭ������ �����ͷ� ����ȯ. (��Ÿ�� �߿� ����ȴ�.)

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