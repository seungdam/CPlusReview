#pragma once


// traditional way to solve template boat problem
// �ϴ� �� ����� �ſ� ��ȿ�����̰� ������
// extern Ű���带 ���ø� �տ� �����ϸ� �ſ� �����ϰ� �ذ��� �� ����.


// decalre string extern template instantiation
// extern template std::ostream& print(std::ostream& os, const std::string& value);
// Ư�� ���� template �Լ��� �ٸ� impentation.cpp�� ����
// �׷��� ������ �ű⿡ �߰��� ����.

// only declare template function
template<typename T>
std::ostream& print(std::ostream& os, const T& value);

// declare non-template member function
void print(const std::string& str);
