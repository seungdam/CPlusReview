#include "pch.h"


// c++14 generic lamda
auto lamda = [](auto x, auto y) { return  x + y; };

class functor
{
public:
	template<typename T>
	T operator()(T x, T y) { return x + y; }
};

template<typename T>
class isequal
{
	T x, y;
public:

	// 이런 식의 template 클래스를 작성할 수 있는데 한가지 의문점이 있음.
	// 어떻게 template parameter가 이 함수들을 동작할 수 있는 적절한 타입인지 판단하는가?
	// 일단 isequal의 compare를 사용하려면 Func은 callable object 여야 하며 x, y는 비교 연산이 가능해야한다.
	// 이를 c++20부터 해당 콘셉에 대해 제공한다. (template parameter constraint)
	//  template specialize라고 부르기도 한다. (탬플릿 특수화)
	isequal(const T& a, const T& b) : x(a), y(b) {}
	template<typename Func>
	bool compare(Func f) { return f(x, y); };
};

using std::cout;

int main()
{
	auto val = lamda(1, 3);
	auto val2 = functor{}(1, 2);

	cout << val << " " << val2 << "\n";

	isequal<int> ie(1, 3);
	cout << "is eqaul 1, 3?: ";
	cout << std::boolalpha << ie.compare([](int x, int y) { return x == y; });

}