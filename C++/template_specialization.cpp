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
// *** Generic Algorithm 함수보다 M.F가 더 효과적인 일부 컨테이너도 이런 식으로 구현한다.
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
	Vector<bool> sv; // Vector<bool>와 가장 유사 >>>> Vector<T> T = bool
	Vector<int> gv; // Vector<T> T = int 와 가장 유사
	Vector<int*> psv;
	gv.identify();
	sv.identify();
	psv.identify();
}