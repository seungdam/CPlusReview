#include <iostream>
#include <string>

using namespace std;


// Operator Overloading

 // Built-in Type�� ��� Ŭ������ ���� ������� �����Ǵ� ��ü�� ���� ����.
 //�׷��� ������ �̷� �⺻ �ڷ����� �ܺο� Operator �Լ��� �����Ǿ� ����.
 //������ ��ġ Class�� Member Function ó�� �����ϴ� ���� ȿ���� ����.
 //Ex) int operator+(int a, int b) 


// Unary vs Binary vs Ternary Operator
// �̷� ���� ���� ���� �Լ��� ���ڸ� �ΰ� �ޱ� ������ Binary Operator��� �θ��⵵ ��. (a + b)
// ������ ��ȣ ǥ������ ����� �����ϴ� ������ ���, ���ڸ� �Ѱ� �ޱ� ������ Unary Operator��� �Ѵ�. (-a)
// Ternary Operator (���׿�����) ���׿����ڴ� �������̴�. a ? b : c ==> operator?(a, b, c)

// User-Defined Type Operator Overloading

// 1. ���� �����ϴ� �⺻���� ���� ��ȣ�ܿ� ���ο� ��ȣ�� ������� �ʴ´�. ==> ���ο� ���� ��ȣ ���� ��� X
// 2. �ش� ��ȣ�� ��Ÿ���� �⺻���� �ǹ̿� ������ ������� �����ε� �����ؾ� �Ѵ�.
// 3. and/or/not�� ���� �� ������, (::, ���ӽ����̽� ������), (, �޸�) (& �ּ� ������)�� �����ε��� �Ұ����ϴ�.. 


// Friend 

//  Friend Ű���带 ���� private ���� �������� ����� ������ �� �ִ�.
// Ex) class A {friend class B;} ==> BŬ������ AŬ������ ���õ� private ����� ������ �� �ִ�.
// ĸ��ȭ�� �������� ���� ����̱� ������ ����� �����ϴ� ���� ����.


// Member vs Non Member function
 
// Member: private ����� �ٷ� ������ �����ϰ�, ������ Ŭ���� ��� �Լ���� Ȱ���� ���� ����.
//  �� ��ü�� ���¸� �����ϴ� �����ڴ� member �Լ��� �����ϴ� ���� ����.
//  �� ����/���� ������ ���� ģ����... +=, =
//  �� �������� �����ϴ� �����ڵ�... [] -> * ()

// Non-Member: �Ϻ� Member�� �������� ���ϰų� ������ �������� �� �� �� �����ϴ� ���� �Լ����� �� ����� ä���ؾ���.
//  �� Ÿ�� ĳ������ �ʿ��� Binary Operator�� ���� Non-Member Fuction���� �����Ѵ�.
//  �� �⺻ ��� / ��Ʈ / ��ġ �����ڿ��� �ʿ�
//  �� Input/Output ������


class MyString
{
	string str;
public:
	MyString() = default;
	MyString(const char* chs) : str(chs) {};
	MyString(const string& s) : str(s) {};

	// Member Operator
	/*MyString operator+(const MyString& rhs) 
	{
		return str + rhs.str;
	}*/

	MyString& operator+=(const MyString& rhs)
	{
		str += rhs.str;
		return *this;
	}
	void print() const { cout << str; }
	friend MyString operator+(const MyString& lhs, const MyString& rhs); // (2-2) Solve Issue
};

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString temp{ lhs };
	temp += rhs; // DRY ��Ģ�� ���� �ڵ� �ߺ��� �ִ��� ������. ����� �߰��Ǵ��� += �����ڸ� �����ϸ� �ȴ�.
	return temp;
}

int main()
{

	int a{ 0 }, b{ 0 };

	int c = a + b; // operator+(a,b); Binary Operator

	// Parameter Constructor
	MyString w{ "World" };
	MyString bang{ "!" };

	// Parameter Constructor
	MyString wbang = w + bang; // call w.operator+(bang); (2-0) OK
	// MyString hi = "hello" + bang;                      (2-1) Not OK
	
	// �����Ϸ��� c style�� ���ڿ�(const char*) �� "hellow"���� 
	// ����� ���õ� ��� ���� Operator�Լ��� �߰��� �� ���� ����. ==> ��? �츮�� ��� �Լ��� �����ڸ� ������ ���� ����
	// �� "hello"�� ���� MyString ��ü�� Ÿ�� ĳ����ó�� ó���� �� �ִ� ��ġ�� �ʿ��ϴ�.
	// Non Member Function���� �̸� �������� �ʿ䰡 ����.

	MyString hi = "hello" + bang; // After Implement Non-Member Function
	wbang.print(); 
	cout << "\n";
	hi.print();

}