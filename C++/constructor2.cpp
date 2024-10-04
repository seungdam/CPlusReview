#include <iostream>

using namespace std;


class Object
{
	int data{ 0 };
public:
	// Class Design Pattern DRY: Dont repeat Yourself
	// 기본 생성자에 관해 많은 오버로딩이 진행되었다면, 중복된 코드가 많다는 것. ==> 리팩토링이 필요
	explicit Object() { cout << "Default Constructor\n"; }
	Object(const int& arg) : data(arg) { cout << "Parameter Constructor\n"; }
	Object(const Object& rhs) { cout << "Copy Constructor\n"; }
	
	// Ref 타입으로 반환시켜야 = 에 관한 중첩 연산자 처리가 가능하다.
	Object& operator=(const Object& rhs)
	{
		data = rhs.data;
		cout << "Copy Assign Operation\n";
		return *this;
	}

	~Object() { }

	// Conversion(형변환) Operator
	// 이럴 경우 해당 형변환 연산에 관해 컴파일러가 암시적으로 활용할 수 있다.
	operator int() const { cout << "Object[" << data << "] " << "Conversion to Int.\n";  return data; }
	 
	// 이런 현상을 방지하기 위해선 explicit 키워드를 활용해야한다.
	// explicit 키워드 활용시, cast 함수를 사용한 명시적인 변환이 아니라면 형변환을 허용하지 않는다.
	explicit operator bool() const { return data; }
};

// Synthesize Function (자동 생성 생성자)
// 컴파일러에 의해 자동으로 생성되는 멤버 함수들
// 1. 기본, 복사, 복사 대입, 소멸은 기본적으로 생성된다.
// 2. 얕은 복사를 수행하기 때문에 깊은 복사를 수행할 땐 직접 구현해야한다.
// 3. 임의로 구현한 생성자가 존재할 경우 컴파일러가 자동 생성을 수행하지 않는다.
/* 4. default / delete 키워드를 통해 컴파일러가 이를 자동 생성하도록 강제할 수 있다.
         *** default 
		      당연하게 작성해야 할 지루한 코드 작성을 방지할 수 있다.(컴파일러가 구현해주기 때문.)
			 이는 코드의 가독성을 향상시키는 것에도 도움이 된다.
			 그리고 멤버의 변화가 있더라도 컴파일러가 자동으로 갱신해준다.

			*** delete
			 선언되어 있는 함수지만 실제론 호출할 순 없다.
			 Conversion이나 Overloading을 방지할 때 활용한다. ==> 주요 활용목적은 복사 생성 및 복사 할당을 방지하는 것
			 default와 달리 사용에 제약이 없다.

	주의해야할 사항은 
	해당 키워드를 사용하더라도 컴파일러가 함수를 synthesize 할 수 없는 경우 delete 처리되기 때문에
	잘 고려해야한다.
 */    

class Test
{
private:
	// (1)과거 방식
	// explicit Test(const Test& rhs) { cout << "Test Copy\n"; } // 복사를 방지하고자 할 땐 private에 해당 연산자를 제공하면 된다.
public:
	explicit Test() = default; // Synthesize Default Constructor
	
	// (1-2)Modern C++ 방식
	explicit Test(const Test& rhs) = delete;
};

// Copy Elison 
// 복사 생성을 줄이기 위해 컴파일러가 스스로 최적화 하는 것.

template<typename Ty>
Ty CopyElisonTempObj()
{
	return Ty();
}

// 이름이 부여된 객체는 Copy Elison이 수행되지 않을 수 있다.

template<typename Ty>
Ty CopyElisonNamedObj()
{
	Ty namedObj;
	return namedObj;
}


int main()
{
	Object obj;
	
	Object obj1{ 1 };
	Object obj2{ obj1 };

	cout << "\n\n===Copy Elison ===\n";
	Object obj3 = CopyElisonNamedObj<Object>();
	Object obj4 = CopyElisonTempObj<Object>();
	cout << "\n\n===Conversion Operator===\n";


	// obj1에 관해 Implicit Conversion 발생. ==> 매개변수 생성자 호출
	// Implicit Conversion은 예기지 못한 현상을 발생하기 때문에 지양하는 것이 좋음.
	// Implicit Conversion의 대표적인 예시로는 stream 객체들이 있음.
	// fstream f("파일명");에 관해 우리는 if(f)를 통해 stream 상태를 확인할 수 있음. 
	int a = obj1 + 100;
	cout << "obj1 + 100 ==> a: " << a << "\n";

	Object obj5(obj1 + 10);
	cout << "Casting obj5 as int: " << static_cast<int>(obj5) << "\n";
	if (obj5) // if, for, while, 삼항연산자 or 논리 연산자 같은 일부 statement에서는 explicit 키워드와 관련없이 항상 암묵적 형변환이 제공된다.
	{
		cout << "obj5's data is available!!\n";
	}
	
}