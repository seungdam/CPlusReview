#include "pch.h"
#include <string>
using namespace std;

void func(int&& rvalue)
{
	cout << "rval: " << rvalue << "\n";
};

void lrfunc(const string& s) { cout << "called lvalue func.\n"; };
void lrfunc(const string&& s) { cout << "called rvalue func.\n"; };


void movestring(string&& s)
{
	string tmp = s;
}

int main()
{
	int x{ 0 };
	int& a = x; // & -> lvalue-ref : 피연산 대상이 되는 개체가 반드시 lvalue여야함.

	const int& b = 3; // const-lvalue-ref: rvalue값도 담을 수 있다.

	// rvalue - ref && : 실제로 reference의 효과를 지니는 것은 아니지만 문법적으로 이렇게 표기 
	// 컴파일러는 이를 보고 유의미한 동작을 수행 --> moveable한 객체를 move를 수행함
	
	func(3);
	// func(x); error
	// func(b); error

	// std::move를 통해 lvalue 값을 rvalue의 형태로 캐스팅시켜 전달할 수 있다.
	func(std::move(x));


	string s{ "hello" };
	string& lrefs{ s };

	cout << "lvalue variable: ";
	lrfunc(s);
	cout << "lvalue reference: ";
	lrfunc(lrefs);
	

	string&& rrefs{ string{"move-str"} }; // move constructor called
	cout << "rvalue variable: ";
	lrfunc("str");
	cout << "rvalue reference: ";
	lrfunc(rrefs); // ***  lvalue-ref function called... 
	cout << "std::move(s): ";
	lrfunc(std::move(s));

}