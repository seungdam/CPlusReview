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
	int& a = x; // & -> lvalue-ref : �ǿ��� ����� �Ǵ� ��ü�� �ݵ�� lvalue������.

	const int& b = 3; // const-lvalue-ref: rvalue���� ���� �� �ִ�.

	// rvalue - ref && : ������ reference�� ȿ���� ���ϴ� ���� �ƴ����� ���������� �̷��� ǥ�� 
	// �����Ϸ��� �̸� ���� ���ǹ��� ������ ���� --> moveable�� ��ü�� move�� ������
	
	func(3);
	// func(x); error
	// func(b); error

	// std::move�� ���� lvalue ���� rvalue�� ���·� ĳ���ý��� ������ �� �ִ�.
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