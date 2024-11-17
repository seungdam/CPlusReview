#include "pch.h"

using namespace std;

int main()
{

	// *** write algorithm 컨테이너 내 요소를 변경하는 알고리즘
	// 당연하게도 cbegin/end는 안된다.

	vector<int> v{ 1,2,3,4,5 };

	replace(v.begin(), v.end(), 1, 2); 
	// (range, target value, replace value);
	// target value를 replace value로 변경한다.
	// 2 2 3 4 5
	
	replace_if(v.begin(), v.end(), [](auto n) { return n % 2 == 0; }, 100); 
	// (range, predicate, replace value);
	// pseudo code
	/*
	for(auto& i : v)
		if(i % 2 == 1) i = 100;
	*/

	// 100 100 3 100 5
	for (auto i : v) cout << i << " ";
	cout << "\n\n";

	// OOO_copy 함수들
	// 해당 버전은 기본 버전들과 달리 데이터의 보존을 필요로 할 때 유용하게 활용된다.
	// 특히 연관 컨테이너에서 유용하게 활용할 수 있다.

	vector<int> v2;
	replace_copy(cbegin(v), cend(v), back_inserter(v2), 1, 2);
	for (auto i : v2) cout << i << " ";
	v2.resize(0);
	cout << "\n"; // v의 원본은 유지하되, 해당 조건에 맞게 변형된 것을 새로운 벡터에 copy

	replace_copy_if(cbegin(v), cend(v), back_inserter(v2), [](auto n) { return (n == 100); } , 2);
	// v2 2 2 3 2 5
	// pseudo code
	/*
	
		for(auto i : v)
		{
			if(predicate) v2.push_back(2);
			else v2.push_back(i);
		}
	*/

	for (auto i : v2) cout << i << " ";
	
}