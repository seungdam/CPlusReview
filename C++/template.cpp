#include "pch.h"

// ===== Generic Programming =====
// Generic 한 프로그래밍은 다양한 데이터 타입에 관한 알고리즘 작성을 용이하게 해주는
// 프로그래밍 기법을 말한다.

// C++언어의 경우 Template을 활용해 작성하는 코드가 이에 해당한다.
// Generic Programming은 생산성과 중복 코드를 줄여줌으로 프로그램의 유지보수에 굉장히 용이하다.
// 하지만, 추가적인 작업이 요구되는 만큼, 실행 비용이 증가하게 된다.

// 하지만 이를 수행함으로써, 전반적인 프로그램의 크기가 줄어들기 때문에 
// 프로그래밍 난이도가 낮아지며, 오류 발생 확률 또한 낮출 수 있다.

// 기본 형태 template<typename/class/template|class 탬플릿 매개변수> class or 함수 선언
// 탬플릿 매개변수로 올 수 있는 타입은 다음과 같다. \
1. 타입 탬플릿 매개변수 \
2. 탬플릿 탬플릿 매개변수 \
3. 타입이 아닌 탬플릿 매개변순


// class vs typename
// 사실 상, 둘은 동일한 기능을 수행한다.
// 상황에 따라, typename ==> 기본 타입 class ==> 클래스 타입으로 구분하여 \
// 작성하는 경우도 많다.



#pragma region template class
template<typename T>
class Base
{
public:
	 T member;
public:
	Base() {}
	~Base() {}
};

class OuterClass
{
public:
	typedef int32 InnerType;
};

template<class J>
class Derived : public Base<typename J::InnerType> // 외부 클래스의 내부타입으로부터 가져오는 것도 가능하다.
{
private:
	J j_memeber;
public:
	Derived()  {}
	void printBaseMemberType() 
	{
		std::cout << "Derived Template Class Type: " << typeid(J).name() << "\n";
		std::cout << "   Base Template Class Type: " << typeid(this->member).name() << "\n";
	}
	~Derived() {}
};
#pragma endregion example

#pragma region class example - STL

template<class Type>
class MyAllocator
{
	// 내가 만든 할당자
public: 
	void Allocate() {}
	void Release() {}
};
// 이런 형태로 활용되기도 한다. 꼭 객체 선언 순간에만 값을 주지 않더라도 이렇게 디폴트값을 세팅할 수 있다.
template<class ValueType, class Allocator = MyAllocator<ValueType>>
class MyStack
{
	// Stack 관련 코드
	Allocator allocator;
public:
	void PrintValueType() { std::cout << "TypeValue Type:" << typeid(ValueType).name() << "\n"; }
	void PrintAllocatorValue() { std::cout << "MyAllocator Type:" << typeid(Allocator).name() << "\n"; }
	void Push() {}
	void Pop()  {}
	void Resize() { allocator.Allocate(); }
};

#pragma endregion
#pragma region template function
// template 함수는 함수 호출 시점에서 탬플릿 타입이 결정된다.
template<class T>
void print(const T& t)
{
	std::cout << t << "\n";
}

// 해당 함수는 일반적인 탬플릿 매개변수와 가변 탬플릿 매개변수를 적용시킨 함수이다.

template<class First, class... Args>
void print(const First& first, const Args&... rest)
{
	std::cout << first;
	if constexpr (sizeof...(rest) > 0) // 가변 타입에 관한 재귀 호출 구현 + constexpr 키워드를 통해 최적화 수행 \
		이러한 반복 처리 방식을 함수 - 인수 팩 확장 이라고 한다.
	{
		std::cout << ", ";
		print(rest...); // 재귀 호출
	}
}

template<class First, class... Arg>
void test(const First& first, const Arg&... rest)
{
	std::cout << "First Type: " << first << " Rest Type: ";
	print(rest...);
}

#pragma endregion

int main()
{
	std::cout << "=== Template Function ===\n";
	print(1);
	print(1, 2, 3, 4); // template 에 들어가는 것은 매개변수, 이렇게 실제로 주어지는 값을 인자로 구분지어 일컫음.
	print(1, 2, 3, "Four", "Five");
	test(13, 100, 200, " Hellow World", 30.0f);

	std::cout << "\n\n === Template Inheritance ===\n";
	Derived<OuterClass> d;
	d.printBaseMemberType(); // OuterClass에 InnerType으로 정의된 int값이 베이스 클래스의 멤버가 될 것이다.

	std::cout << "\n\n === MyStack ===\n";
	MyStack<int32> s;
	s.PrintValueType();
	s.PrintAllocatorValue();


	std::cout << "\n\n===std::vector<int>===\n";
	std::cout << "TypeValue Type:" << typeid(std::vector<int32>::value_type).name() << "\n";
	std::cout << "Allocator Type:" << typeid(std::vector<int32>::allocator_type).name() << "\n";
}