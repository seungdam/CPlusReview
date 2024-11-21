#include "pch.h"

using namespace std;


int main()
{
	// *** write-only algorithm 어떤 결과값을 read하는 것이 아닌 오직 쓰기만 하는 알고리즘 함수들

	vector<int> v(10);
	fill(v.begin(), v.end(), 42); // fill all element as 42

	auto iter = fill_n(v.begin(), 5, 10); // fill 5 element as 10 from begin and return next iterator
	fill(iter, v.end(), 99);

	// 반드시 벡터는 빈 벡터가 아니여야한다.
	for (auto i : v) cout << i << " ";
	cout << "\n";

	// back_inserter를 활용해 빈 벡터에서도 활용가능
	vector<int> ev;
	auto iter2 = fill_n(back_inserter(ev), 5, 42);

	generate(v.begin(), v.end(), [n = 0]() mutable {++n; return n * n; });
	generate_n(back_inserter(ev), 5, [n = 10]() mutable {++n; return n * n; });
	for (auto i : v) cout << i << " ";
	cout << "\n";
}