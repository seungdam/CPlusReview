#include "pch.h"

using namespace std;

// *** std::swap
// noexcept(no-thrown)�� �����ϴ� c++ library function
// std::swap�� ���ڿ� ���� �ƹ��� ������ �𸣱� ������ �����ϰ� �����Ѵ�.
// ==> just copied it
// �̸� �� �� ȿ�������� Ȱ���ϱ� ���ؼ� overloading �۾��� �ʿ��ϴ�. ex) ����� ���� Ŭ���� ��� �Բ� Ȱ���ϱ�
// 

// std::sort�� ���������� �� swap �Լ��� ȣ���Ѵ�.

class Sample
{
	int32 id;
	int32 data;
public:
	Sample() {};
	Sample(int32 a, int32 b) : id(a), data(b) {};

	friend void swap(Sample& rhs, Sample& lhs) noexcept;
	friend ostream& operator<<(ostream& os, const Sample& lhs);
};

inline void swap(Sample& rhs, Sample& lhs) noexcept
{
	using std::swap;
	swap(rhs.id, lhs.id);
	swap(rhs.data, lhs.data);
}

inline ostream& operator<<(ostream& os, const Sample& lhs)
{
	os << lhs.id << " : " << lhs.data << " Address: " << &lhs.data << "\n";
	return os;
}

int main()
{
	Sample a{ 0,100 };
	Sample b{ 1,300 };
	cout << "A " << a;
	cout << "B " << b;

	std::swap(a, b);

	cout << "A " << a;
	cout << "B " << b;
}