#include "pch.h"

using namespace std;
// ��ü�� ��ġ callable �� ��ó�� ���� ����
// �̷��� ��ü�� Functor��� �Ѵ�. �Լ��� ���δ� Wrapper Class��� �ؼ��ϴ� �͵� ����.
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