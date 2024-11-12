#include "pch.h"

using namespace std;

// *** key 값에 따라 정렬을 수행하기 때문에 key에 해당하는 타입은 < 연산자를 제공해야한다.

int main()
{
	map<string, int> m;
	set<int> s;

	//
	auto [iterator, result] = m.insert({ "A"s, 100 }); // key가 없는 값이라면 insert를 수행
	m["A"] = 200; // key가 없으면 insert 아니라면 assign 수행

	
	// *** C++17
	auto [iter1, res1] = m.insert_or_assign("Gram"s, 10);
	auto [iter2, res2] = m.insert_or_assign("Gram"s, 12);

	// *** multimap & multiset

	multimap<string, int> scores;
	scores.insert({ "Gram"s, 100 });
	scores.insert({ "Gram"s, 55 });
	scores.insert({ "A"s, 66 });
	scores.insert({ "A"s, 65 });
	scores.insert({ "A"s, 22 });
	scores.insert({ "B"s, 77 });
	scores.insert({"C"s, 88});

	for (auto [f, s] : scores) cout << f << ":" << s << "\n";
	scores.erase("Gram");
	cout << "\n\n"; // 멀티맵은 동일한 키의 개체를 모두 삭제한다.
	for (auto [f, s] : scores) cout << f << ":" << s << "\n";
	// 일부 요소만 삭제하려면, count와 find를 활용해야한다.
	
	auto iter = scores.find("Gram");
	while (iter != end(scores))
	{
		if ((*iter).second != 66) ++iter;
		else scores.erase(iter);
	}
	// *** 동일한 key를 가진 서브 집합에 관해 lower_bound와 upper_bound를 활용해 쉽게 이터레이터 범위를 도출 가능
	// find를 활용하는 것보다 좀 더 효율적인 코드 작성이 가능하다.
	auto aBegin = scores.upper_bound("A");
	auto aEnd = scores.lower_bound("A"); // "B"

	// equal_range() --> lower와 upperbound에 해당하는 이터레이터 값을 pair의 형태로 반환한다.

	// C++17 struct binding
	auto [bBegin, bEnd] = scores.equal_range("B");
	auto retval = find_if(aBegin, aEnd, [](auto elm) { return elm.second == 66; })
	

}