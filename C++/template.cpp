#include "pch.h"

// ===== Generic Programming =====
// Generic �� ���α׷����� �پ��� ������ Ÿ�Կ� ���� �˰��� �ۼ��� �����ϰ� ���ִ�
// ���α׷��� ����� ���Ѵ�.

// C++����� ��� Template�� Ȱ���� �ۼ��ϴ� �ڵ尡 �̿� �ش��Ѵ�.
// Generic Programming�� ���꼺�� �ߺ� �ڵ带 �ٿ������� ���α׷��� ���������� ������ �����ϴ�.
// ������, �߰����� �۾��� �䱸�Ǵ� ��ŭ, ���� ����� �����ϰ� �ȴ�.

// ������ �̸� ���������ν�, �������� ���α׷��� ũ�Ⱑ �پ��� ������ 
// ���α׷��� ���̵��� ��������, ���� �߻� Ȯ�� ���� ���� �� �ִ�.

// �⺻ ���� template<typename/class/template|class ���ø� �Ű�����> class or �Լ� ����
// ���ø� �Ű������� �� �� �ִ� Ÿ���� ������ ����. \
1. Ÿ�� ���ø� �Ű����� \
2. ���ø� ���ø� �Ű����� \
3. Ÿ���� �ƴ� ���ø� �Ű�����


// class vs typename
// ��� ��, ���� ������ ����� �����Ѵ�.
// ��Ȳ�� ����, typename ==> �⺻ Ÿ�� class ==> Ŭ���� Ÿ������ �����Ͽ� \
// �ۼ��ϴ� ��쵵 ����.



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
class Derived : public Base<typename J::InnerType> // �ܺ� Ŭ������ ����Ÿ�����κ��� �������� �͵� �����ϴ�.
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
	// ���� ���� �Ҵ���
public: 
	void Allocate() {}
	void Release() {}
};
// �̷� ���·� Ȱ��Ǳ⵵ �Ѵ�. �� ��ü ���� �������� ���� ���� �ʴ��� �̷��� ����Ʈ���� ������ �� �ִ�.
template<class ValueType, class Allocator = MyAllocator<ValueType>>
class MyStack
{
	// Stack ���� �ڵ�
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
// template �Լ��� �Լ� ȣ�� �������� ���ø� Ÿ���� �����ȴ�.
template<class T>
void print(const T& t)
{
	std::cout << t << "\n";
}

// �ش� �Լ��� �Ϲ����� ���ø� �Ű������� ���� ���ø� �Ű������� �����Ų �Լ��̴�.

template<class First, class... Args>
void print(const First& first, const Args&... rest)
{
	std::cout << first;
	if constexpr (sizeof...(rest) > 0) // ���� Ÿ�Կ� ���� ��� ȣ�� ���� + constexpr Ű���带 ���� ����ȭ ���� \
		�̷��� �ݺ� ó�� ����� �Լ� - �μ� �� Ȯ�� �̶�� �Ѵ�.
	{
		std::cout << ", ";
		print(rest...); // ��� ȣ��
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
	print(1, 2, 3, 4); // template �� ���� ���� �Ű�����, �̷��� ������ �־����� ���� ���ڷ� �������� ������.
	print(1, 2, 3, "Four", "Five");
	test(13, 100, 200, " Hellow World", 30.0f);

	std::cout << "\n\n === Template Inheritance ===\n";
	Derived<OuterClass> d;
	d.printBaseMemberType(); // OuterClass�� InnerType���� ���ǵ� int���� ���̽� Ŭ������ ����� �� ���̴�.

	std::cout << "\n\n === MyStack ===\n";
	MyStack<int32> s;
	s.PrintValueType();
	s.PrintAllocatorValue();


	std::cout << "\n\n===std::vector<int>===\n";
	std::cout << "TypeValue Type:" << typeid(std::vector<int32>::value_type).name() << "\n";
	std::cout << "Allocator Type:" << typeid(std::vector<int32>::allocator_type).name() << "\n";
}