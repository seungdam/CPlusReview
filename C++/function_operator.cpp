#include "pch.h"

using namespace std;
// 객체를 마치 callable 한 것처럼 구현 가능
// 이러한 객체를 Functor라고 한다. 함수를 감싸는 Wrapper Class라고 해석하는 것도 좋다.
class ceven
{
public:
	bool operator()(const int& elm) { return ((elm % 2) == 0); }
};

void do_it(const vector<int>& v, ceven& is_even)
{
	for (const auto& elm : v)
		if (is_even(elm)) cout << elm << " is even number.\n";
}

int main()
{
	ceven ev;
	vector<int> v{ 1,11,100,200,30 };

	do_it(v, ev);


}