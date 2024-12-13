#include "pch.h"
#include "print.h"

using std::cout;

// define template-func here
template<typename T>
std::ostream& print(std::ostream& os, const T& value)
{
	return os << value;
}

// decalre string template instantiation
template std::ostream& print(std::ostream& os, const std::string& value);


int main()
{
	std::string s{"Hello"};
	print(cout, s) << "\n";
	print(s);
}