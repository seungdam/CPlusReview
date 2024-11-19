#include "pch.h"

using namespace std;

int main()
{
	// *** std::merge(range1,range2, dest) 
	// 정렬된 두 범위의 요소를 합친 결과물을 dest에 분포시킨다. 
	// 이때 dest는 < operator에 의해 정렬된 결과를 가진다.
	// set theory를 기반으로 한다.(합집합)
	// back_inserter 대신 크기를 가지는 집합을 넣어도 상관없다.
	vector<int> v{  1,2,3 };
	vector<int> v2{ 2,3,4 };
	vector<int> v3;
	vector<int> v4;
	vector<int> v5;

	merge(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v3));
	for (auto i : v3) cout << i << " ";
	cout << "\n";
	// *** set_intersection : 두 범위의 교집합에 해당하는 원소만 가져온다. (set-theory 교집합)
	set_intersection(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v4)); // v4 : 2, 3
	for (auto i : v4) cout << i << " ";
	cout << "\n";
	// *** set_union(): 두 정렬된 범위를 합하되, 중복된 요소는 제거한다.
	set_union(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v5)); // 1. 2. 3. 4;
	for (auto i : v5) cout << i << " ";

}