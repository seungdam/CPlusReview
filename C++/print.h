#pragma once


// traditional way to solve template boat problem
// 일단 이 방식은 매우 비효율적이고 복잡함
// extern 키워드를 탬플릿 앞에 선언하면 매우 간단하게 해결할 수 있음.


// decalre string extern template instantiation
// extern template std::ostream& print(std::ostream& os, const std::string& value);
// 특수 버전 template 함수를 다른 impentation.cpp에 선언
// 그러면 앞으로 거기에 추가될 것임.

// only declare template function
template<typename T>
std::ostream& print(std::ostream& os, const T& value);

// declare non-template member function
void print(const std::string& str);
