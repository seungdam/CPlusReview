#include "pch.h"
#include <functional>


using std::cout;
using namespace std::literals::string_literals;

// *** member-function-ptr
// non-member-function ptr syntax와 다름
// 그리고 해당 m.f를 호출할 객체가 존재해야함.
// 직접 호출하는 것은 불가능 -> 반드시 역참조를 수행한 후에 해야함. ==> m.f-ptr은 callable-object가 아님
// 기존에 compiler가 자동으로 제공하는 this 포인터를 직접 제공해줘야할 수 있음.


// *** when should we use?
// 1. 동시성 프로그래밍을 수행할 때 --> thread 인자로 객체의 m.f를 넘겨줄 때
// 2. run-time 중에 결정하도록 만들 때
// 3. 여러 객체 중 m.f를 호출할 객체를 결정해야할 때 std::bind와 함께 활용

void non_mf() { cout << "Hello\n";  return; }

class Object
{
public:
	void func(int a, const std::string& str) { cout << "A: " << a << " str: " << str << "\n"; };
};

// define pfunc as a pointer to m.f of obj

int main()
{
	// 1. 일반적인 function-ptr
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