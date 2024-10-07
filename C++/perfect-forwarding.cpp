#include "pch.h"
using namespace std;
// *** nested-ref : 계속해서 중첩되는 Reference... 뭔가 문제가 될 수 있을 것 같다.
// 하지만 컴파일러가 알아서 Reference Collapsing(참조 축소) 작업을 통해 이를 처리한다.

// lvaue-ref (T&)
// T& & ==> T& (reference-collapsing)

// rvalue-ref (T&&)
// T&&  & ((Test&&)&) ==> lvalue-ref
// T&& &&((Test&&)&&) ==> rvalue-ref
void func(int& ir)
{
	cout << "lvalue-ref call func.\n";
}

// Forwarding Reference (참조전달)
// void func(A&& x) {}에 관해.. x는 항상 xvalue or prvalue여야 함.
// 근데 만약 해당 func이 탬플릿 타입이라면?? 앞서 말했던 nested-ref가 발생할 수 있다.

// &&의미가 rvalue-ref에서 generic으로 바뀜으로써 다른 기능을 수행하게 된다.
// 이때 x는 fowarding-ref라고 한다.

class Test {};

template<class T>
void forward_ref_func(T&& x) // ==> binding as rvalue lvalue. 모든 타입을 바인딩할 수 있다.
{
	cout << "forword-ref func called.\n";
}



// ===== Forwarding =======
// 하나 이상의 함수가 동일한 인자들을 연속적으로 다른 함수에게 전달하는 것
// ex) void f(args..) { g(args..);} func은 func2에게 args를 forwarding하고 있는 것이다.

// ==== Perfect Forwarding ====
// 이때 전달되는 인수에 관해, 각각의 함수가 동일한 속성을 가지게 전달하는 것을 퍼펙트 포워딩이라고 한다.
// 이는 생성자를 호출하는 함수에 관해서 유용하게 활용될 수 있다.
// 또는 가변 인자 탬플릿에서 유용하게 활용될 수 있다.

// make-pair는 대표적인 perfect forwarding을 제공하는 표준 라이브러리 함수다.

void g(Test&& t) {   cout << "move to g(x)\n"; }
void g(Test& t) {   cout << "ref to g(x)\n"; }
void g(const Test& t)   {   cout << "const ref to g(x)\n"; }
template<class T>
void perfect_forwarding(T&& x) // ==> binding as rvalue lvalue. 모든 타입을 바인딩할 수 있다.
{
	cout << "Perfect Forwarding to Func g(x)\n";
	g(std::forward<T>(x));

}

// make-pair 동작 원리
class Object
{
	string str;
public:
	Object(Object&& other) noexcept : str(move(other.str))  {}
	Object(const Object& other) : str(other.str) {}
	Object(string&& s) noexcept : str(std::move(s)) { std::cout << "move\n"; }
	Object(const string& s) : str(s) { std::cout << "copy\n"; }
};

template<class T>
Object make_obj(T&& x)
{

	return Object(std::forward<T>(x));
}


int main()
{
	int a{ 100 };
	using int_ref = int&;
	
	int_ref ar = a;
	int_ref arr = ar; // ref의 ref인 arr
	func(arr); // 컴파일러가 참조 축소 작업을 했기 때문에 ref-ref 개체를 ref로 인자를 넘길 수 있다.


	Test t;
	Test& tr{ t }; // Test&

	forward_ref_func(t);  // T = Test& T&& ==> Test& (lvalue-collapsing)
	forward_ref_func(tr); // T = Test& T&& ==> Test& (lvalue-collapsing)
	forward_ref_func(std::move(t)); // T = Test() T&& ==> Test&& 

	cout << "\n\n";

	Test x; // lvalue
	perfect_forwarding(x); // lvalue 이므로 T = Test&로 추론 
						   // <탬플릿 인수 추론에 의거>
	                       //  T&& => Test& && ==> Test&
	const Test cx; 
	perfect_forwarding(cx); // T = const Test&  
							// T&& = const Test& && ==> const Test&

	perfect_forwarding(std::move(x)); 
							// T = Test
							// T&& ==> Test&& ==> Test&&
	// 그냥 함수를 구현하면 이동생략이 일어나기 때문에 std::forward를 함께 사용해주자.
	// std::forward는 move와 동일한 기능을 수행한다. 그때 이 과정을 ref-collapsing을 통해 동작한다.
	
	cout << "\n\nperfect-forwarding example\n";
	string str{ "Hellow" };
	Object obj1 = make_obj(str);
	Object obj2 = make_obj(std::move(str));
}