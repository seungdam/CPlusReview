#include "pch.h"
#include <typeinfo>
using std::cout;


// generic version
template<typename T>
class Vector
{
public:
	void identify() { cout <<  "Generic Version: Vector<" << typeid(T).name() << ">\n"; }

};

// specialized version
// *** Generic Algorithm �Լ����� M.F�� �� ȿ������ �Ϻ� �����̳ʵ� �̷� ������ �����Ѵ�.
template<>
class Vector<bool>
{
public:
	void identify() { cout<< "Specialized Version: Vector<bool>\n"; }
};

// partial specialized version
// only for value, class type not for functional type
template<typename T>
class Vector<T*>
{
public:
	void identify() { cout << "Partial Specialized Version: Vector<" << typeid(T).name() << "*>\n"; }
};

int main()
{
	Vector<bool> sv; // Vector<bool>�� ���� ���� >>>> Vector<T> T = bool
	Vector<int> gv; // Vector<T> T = int �� ���� ����
	Vector<int*> psv;
	gv.identify();
	sv.identify();
	psv.identify();
}