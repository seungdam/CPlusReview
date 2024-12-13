#include "pch.h"
#include <iomanip>
#include <type_traits>

using std::cout;

class A {};

int main()
{
	cout << std::setw(25) << std::right << std::boolalpha << "is-int arithmetic? " << std::is_arithmetic<int>::value << "\n";
	cout << std::setw(25) << std::boolalpha << "is-A class? " << std::is_class<A>::value << "\n";
	cout << std::setw(25) << std::boolalpha << "is-int floating-point? " << std::is_floating_point<int>::value << "\n";
	cout << std::setw(25) << std::boolalpha << "is const char* pointer? " << std::is_pointer<const char*>::value << "\n";
}