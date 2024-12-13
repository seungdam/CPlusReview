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

	// �̷� ���� template Ŭ������ �ۼ��� �� �ִµ� �Ѱ��� �ǹ����� ����.
	// ��� template parameter�� �� �Լ����� ������ �� �ִ� ������ Ÿ������ �Ǵ��ϴ°�?
	// �ϴ� isequal�� compare�� ����Ϸ��� Func�� callable object ���� �ϸ� x, y�� �� ������ �����ؾ��Ѵ�.
	// �̸� c++20���� �ش� �ܼ��� ���� �����Ѵ�. (template parameter constraint)
	//  template specialize��� �θ��⵵ �Ѵ�. (���ø� Ư��ȭ)
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