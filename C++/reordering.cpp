#include "pch.h"

using namespace std;

inline void print2(const vector<int>& v)
{
	for (auto i : v) cout << i << " ";
	cout << "\r";
}

int main()
{

	// *** reverse(range) 
	// 해당 범위의 정렬 순서를 뒤바꾼다. 당연하게도 const iterator를 범위로 주어선 x
	// value값은 변하지 x 내부적으로 swap을 호출함
	// _copy 버전도 있음

	auto v{ vector<int>{1,2,3,4} };
	auto v2{ vector<int>{} };

	reverse(begin(v), end(v));
	reverse_copy(cbegin(v), cend(v), back_inserter(v2));
	print(v);
	print(v2);

	// *** rotate(begin, pivot, end)
	// advance와 함께 활용된다.
	// pivot에 해당하는 벨류가 begin의 범위로 오는 것으로 회전시킨다.
	
	auto pivot = begin(v2);
	advance(pivot, 2);
	rotate(begin(v2), pivot, end(v2)); // 3 4 1 2
	print(v2);


	// 1 2 3 4
	// 4 3 2 1
	// 3 2 1 4

	for (int i = 0; i < 5; ++i)
	{
		auto pivot2 = rbegin(v);
		advance(pivot2, 1); // 3
		rotate(rbegin(v), pivot2, rend(v)); // 2 3 4 1
		print2(v);
		Sleep(1000);
	}
	cout << "\n";
	// _copy 버전도 존재하나, back_inserter를 활용할 수 없음에 주의해야함

}