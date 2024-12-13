#include "pch.h"
#include <functional>


using std::cout;
using namespace std::literals::string_literals;

// *** member-function-ptr
// non-member-function ptr syntax�� �ٸ�
// �׸��� �ش� m.f�� ȣ���� ��ü�� �����ؾ���.
// ���� ȣ���ϴ� ���� �Ұ��� -> �ݵ�� �������� ������ �Ŀ� �ؾ���. ==> m.f-ptr�� callable-object�� �ƴ�
// ������ compiler�� �ڵ����� �����ϴ� this �����͸� ���� ����������� �� ����.


// *** when should we use?
// 1. ���ü� ���α׷����� ������ �� --> thread ���ڷ� ��ü�� m.f�� �Ѱ��� ��
// 2. run-time �߿� �����ϵ��� ���� ��
// 3. ���� ��ü �� m.f�� ȣ���� ��ü�� �����ؾ��� �� std::bind�� �Բ� Ȱ��

void non_mf() { cout << "Hello\n";  return; }

class Object
{
public:
	void func(int a, const std::string& str) { cout << "A: " << a << " str: " << str << "\n"; };
};

// define pfunc as a pointer to m.f of obj

int main()
{
	// 1. �Ϲ����� function-ptr
	auto nmptr1 = non_mf;
	void(*nmptr2)() = non_mf;
	

	// 2. member-function-ptr
	void (Object::*pfunc) (int, const std::string&); // type define
	pfunc = &Object::func;
	// 2-1. call
	Object obj; // create object
	(obj.*pfunc)(42, "Hello"s); // deference m.f ptr (*pfunc)
	((&obj)->*pfunc)(50, "Hello"s); // how to use with class pointer

	// 2-2. C++11 feature

	// use auto keyword
	auto pfunc2 = &Object::func;
	(obj.*pfunc2)(100, "Ho"s);

	// use alias
	using PMFunc = void(Object::*)(int, const std::string&);
	PMFunc a = &Object::func;
	(obj.*a)(100, "Hogu"s);

	// 3. std::mem_fn from <functional>
	// convert m.f ptr to callable object

	auto co_mf = std::mem_fn(pfunc);
	co_mf(obj, 100, "Hi"s); // this-ptr , arg

	// 3-2. with std::bind
	
	auto bmf = std::bind(&Object::func, &obj,std::placeholders::_1, "Cat");
	std::function<void(int)> f = bmf;
	f(90);
	bmf(100);
}