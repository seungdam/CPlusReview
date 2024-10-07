#include <iostream>
#include <string>

using namespace std;


// Operator Overloading

 // Built-in Type의 경우 클래스와 같은 방식으로 생성되는 객체로 보지 않음.
 //그렇기 때문에 이런 기본 자료형은 외부에 Operator 함수가 구현되어 있음.
 //하지만 마치 Class의 Member Function 처럼 동작하는 듯한 효과를 보임.
 //Ex) int operator+(int a, int b) 


// Unary vs Binary vs Ternary Operator
// 이런 덧셈 연산 같은 함수는 인자를 두개 받기 때문에 Binary Operator라고 부르기도 함. (a + b)
// 하지만 부호 표현같은 기능을 수행하는 연산의 경우, 인자를 한개 받기 때문에 Unary Operator라고도 한다. (-a)
// Ternary Operator (삼항연산자) 삼항연산자는 예외적이다. a ? b : c ==> operator?(a, b, c)

// User-Defined Type Operator Overloading

// 1. 언어에서 제공하는 기본적인 연산 기호외에 새로운 기호를 사용하지 않는다. ==> 새로운 연산 기호 구현 허용 X
// 2. 해당 기호가 나타내는 기본적인 의미와 연관된 방식으로 오버로딩 수행해야 한다.
// 3. and/or/not과 같은 논리 연산자, (::, 네임스페이스 스코프), (, 콤마) (& 주소 연산자)는 오버로딩이 불가능하다.. 


// Friend 

//  Friend 키워드를 통해 private 접근 지정자의 멤버를 접근할 수 있다.
// Ex) class A {friend class B;} ==> B클래스는 A클래스와 관련된 private 멤버를 접근할 수 있다.
// 캡슐화를 보장하지 않은 방식이기 때문에 사용을 지양하는 것이 좋다.


// Member vs Non Member function
 
// Member: private 멤버에 바로 접근이 가능하고, 연관된 클래스 멤버 함수들과 활용할 수도 있음.
//  ㄴ 객체의 상태를 변경하는 연산자는 member 함수로 구현하는 것이 좋다.
//  ㄴ 복합/증감 연산자 같은 친구들... +=, =
//  ㄴ 역참조를 수행하는 연산자들... [] -> * ()

// Non-Member: 일부 Member로 구현하지 못하거나 비멤버로 구현했을 때 더 잘 동작하는 연산 함수들은 이 방식을 채택해야함.
//  ㄴ 타입 캐스팅이 필요한 Binary Operator의 경우는 Non-Member Fuction으로 구현한다.
//  ㄴ 기본 산술 / 비트 / 등치 연산자에서 필요
//  ㄴ Input/Output 연산자


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
	temp += rhs; // DRY 규칙에 따라 코드 중복을 최대한 피하자. 멤버가 추가되더라도 += 연산자만 수정하면 된다.
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
	
	// 컴파일러는 c style의 문자열(const char*) 인 "hellow"에서 
	// 연산과 관련된 어떠한 전역 Operator함수를 발견할 수 없기 때문. ==> 왜? 우리는 멤버 함수로 연산자를 구현해 놨기 때문
	// 즉 "hello"에 관해 MyString 객체로 타입 캐스팅처럼 처리할 수 있는 장치가 필요하다.
	// Non Member Function으로 이를 구현해줄 필요가 있음.

	MyString hi = "hello" + bang; // After Implement Non-Member Function
	wbang.print(); 
	cout << "\n";
	hi.print();

}