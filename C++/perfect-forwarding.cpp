#include "pch.h"
using namespace std;
// *** nested-ref : ����ؼ� ��ø�Ǵ� Reference... ���� ������ �� �� ���� �� ����.
// ������ �����Ϸ��� �˾Ƽ� Reference Collapsing(���� ���) �۾��� ���� �̸� ó���Ѵ�.

// lvaue-ref (T&)
// T& & ==> T& (reference-collapsing)

// rvalue-ref (T&&)
// T&&  & ((Test&&)&) ==> lvalue-ref
// T&& &&((Test&&)&&) ==> rvalue-ref
void func(int& ir)
{
	cout << "lvalue-ref call func.\n";
}

// Forwarding Reference (��������)
// void func(A&& x) {}�� ����.. x�� �׻� xvalue or prvalue���� ��.
// �ٵ� ���� �ش� func�� ���ø� Ÿ���̶��?? �ռ� ���ߴ� nested-ref�� �߻��� �� �ִ�.

// &&�ǹ̰� rvalue-ref���� generic���� �ٲ����ν� �ٸ� ����� �����ϰ� �ȴ�.
// �̶� x�� fowarding-ref��� �Ѵ�.

class Test {};

template<class T>
void forward_ref_func(T&& x) // ==> binding as rvalue lvalue. ��� Ÿ���� ���ε��� �� �ִ�.
{
	cout << "forword-ref func called.\n";
}



// ===== Forwarding =======
// �ϳ� �̻��� �Լ��� ������ ���ڵ��� ���������� �ٸ� �Լ����� �����ϴ� ��
// ex) void f(args..) { g(args..);} func�� func2���� args�� forwarding�ϰ� �ִ� ���̴�.

// ==== Perfect Forwarding ====
// �̶� ���޵Ǵ� �μ��� ����, ������ �Լ��� ������ �Ӽ��� ������ �����ϴ� ���� ����Ʈ �������̶�� �Ѵ�.
// �̴� �����ڸ� ȣ���ϴ� �Լ��� ���ؼ� �����ϰ� Ȱ��� �� �ִ�.
// �Ǵ� ���� ���� ���ø����� �����ϰ� Ȱ��� �� �ִ�.

// make-pair�� ��ǥ���� perfect forwarding�� �����ϴ� ǥ�� ���̺귯�� �Լ���.

void g(Test&& t) {   cout << "move to g(x)\n"; }
void g(Test& t) {   cout << "ref to g(x)\n"; }
void g(const Test& t)   {   cout << "const ref to g(x)\n"; }
template<class T>
void perfect_forwarding(T&& x) // ==> binding as rvalue lvalue. ��� Ÿ���� ���ε��� �� �ִ�.
{
	cout << "Perfect Forwarding to Func g(x)\n";
	g(std::forward<T>(x));

}

// make-pair ���� ����
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
	int_ref arr = ar; // ref�� ref�� arr
	func(arr); // �����Ϸ��� ���� ��� �۾��� �߱� ������ ref-ref ��ü�� ref�� ���ڸ� �ѱ� �� �ִ�.


	Test t;
	Test& tr{ t }; // Test&

	forward_ref_func(t);  // T = Test& T&& ==> Test& (lvalue-collapsing)
	forward_ref_func(tr); // T = Test& T&& ==> Test& (lvalue-collapsing)
	forward_ref_func(std::move(t)); // T = Test() T&& ==> Test&& 

	cout << "\n\n";

	Test x; // lvalue
	perfect_forwarding(x); // lvalue �̹Ƿ� T = Test&�� �߷� 
						   // <���ø� �μ� �߷п� �ǰ�>
	                       //  T&& => Test& && ==> Test&
	const Test cx; 
	perfect_forwarding(cx); // T = const Test&  
							// T&& = const Test& && ==> const Test&

	perfect_forwarding(std::move(x)); 
							// T = Test
							// T&& ==> Test&& ==> Test&&
	// �׳� �Լ��� �����ϸ� �̵������� �Ͼ�� ������ std::forward�� �Բ� ���������.
	// std::forward�� move�� ������ ����� �����Ѵ�. �׶� �� ������ ref-collapsing�� ���� �����Ѵ�.
	
	cout << "\n\nperfect-forwarding example\n";
	string str{ "Hellow" };
	Object obj1 = make_obj(str);
	Object obj2 = make_obj(std::move(str));
}