#include "pch.h"
#include <tuple>

using namespace std;

void func(int a, float b,  char c)
{
	std::cout << a << " " << b << " " << c << "\n";
}

struct Object
{
	int a;
	float b;
	char c;
};

int main()
{
	// C++11
	auto t = tuple<int, float, char>{ 10, 0.1f, 't' };
	auto t2 = make_tuple<int, float, char>(10, 0.5f, 'c');
	auto t3 = make_tuple<int, int, int>(1, 2, 3);

	int x; float y; char z; 

	std::tie(x, y, z) = t; // C++11
	auto [i, f, c] = t; // C++17 structure binding


	x = std::get<0>(t); // = std::get<int> // std::get<type> is only for unique type tuple's
	y = std::get<1>(t); // = std::get<float>
	z = std::get<2>(t); // = std::get<char>
	


	std::apply(func, t);
	auto obj = std::make_from_tuple<Object>(t); // Binding in to Constructor

}