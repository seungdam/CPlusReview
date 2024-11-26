#include "pch.h"

using namespace std;

// *** std::swap
// noexcept(no-thrown)를 보장하는 c++ library function
// std::swap은 인자에 관한 아무런 정보도 모르기 때문에 무식하게 동작한다.
// ==> just copied it
// 이를 좀 더 효율적으로 활용하기 위해선 overloading 작업이 필요하다. ex) 사용자 정의 클래스 등과 함께 활용하기
// 

// std::sort도 내부적으로 이 swap 함수를 호출한다.

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