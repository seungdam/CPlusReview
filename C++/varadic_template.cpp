#include "pch.h"
#include <tuple>
// *** variadic argument
// 가변길이 인자
// printf(const char* fmt, ...)


template<typename... Args>
void func(Args... args)
{
	std::cout << "Size of Arguments " << sizeof...(args) << "\n";
}

template<typename... Args>
void func2(Args... args)
{
	std::cout << "first arguments of tuple is [";
	auto t = std::make_tuple(args...);
	auto first = get<0>(t);

	std::cout << first << "]\n";
}



// *** Recrusive Function Call

template<typename T>
void RecrusiveFunc(T t)
{
	std::cout << "Last Member is... " << t << "\n";
}

template<typename T, typename... Args>
void RecrusiveFunc(T t, Args... args)
{
	std::cout << "Arg Cnt: " << sizeof...(args) << "\n";
	std::cout << "Recrusive Call... " << t << "\n";
	RecrusiveFunc(args...);
}
int main()
{
	func(1, 2.f, 3.0, "hello");
	func2(42, 2.f, 3, "hello");


	RecrusiveFunc(1, 2, 3, 4, 5.0, 9.1, 10, "bye");
}