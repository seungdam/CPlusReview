#include "pch.h"

using std::cout;

int main()
{
	int x;
	std::cin >> x;
	const int y{ x }; // ok
	// constexpr int w{ x }; not ok   constexpr(c++11~)

	const int z {9};
	int arr[z + 3] {}; // ok const expression + literals = const expressions
}