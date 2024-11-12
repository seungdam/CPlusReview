#include "pch.h"

using namespace std;

// *** key ���� ���� ������ �����ϱ� ������ key�� �ش��ϴ� Ÿ���� < �����ڸ� �����ؾ��Ѵ�.

int main()
{
	map<string, int> m;
	set<int> s;

	//
	auto [iterator, result] = m.insert({ "A"s, 100 }); // key�� ���� ���̶�� insert�� ����
	m["A"] = 200; // key�� ������ insert �ƴ϶�� assign ����

	
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
	cout << "\n\n"; // ��Ƽ���� ������ Ű�� ��ü�� ��� �����Ѵ�.
	for (auto [f, s] : scores) cout << f << ":" << s << "\n";
	// �Ϻ� ��Ҹ� �����Ϸ���, count�� find�� Ȱ���ؾ��Ѵ�.
	
	auto iter = scores.find("Gram");
	while (iter != end(scores))
	{
		if ((*iter).second != 66) ++iter;
		else scores.erase(iter);
	}
	// *** ������ key�� ���� ���� ���տ� ���� lower_bound�� upper_bound�� Ȱ���� ���� ���ͷ����� ������ ���� ����
	// find�� Ȱ���ϴ� �ͺ��� �� �� ȿ������ �ڵ� �ۼ��� �����ϴ�.
	auto aBegin = scores.upper_bound("A");
	auto aEnd = scores.lower_bound("A"); // "B"

	// equal_range() --> lower�� upperbound�� �ش��ϴ� ���ͷ����� ���� pair�� ���·� ��ȯ�Ѵ�.

	// C++17 struct binding
	auto [bBegin, bEnd] = scores.equal_range("B");
	auto retval = find_if(aBegin, aEnd, [](auto elm) { return elm.second == 66; })
	

}