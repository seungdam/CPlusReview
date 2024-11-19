#include "pch.h"

using namespace std;

int main()
{
	// *** std::merge(range1,range2, dest) 
	// ���ĵ� �� ������ ��Ҹ� ��ģ ������� dest�� ������Ų��. 
	// �̶� dest�� < operator�� ���� ���ĵ� ����� ������.
	// set theory�� ������� �Ѵ�.(������)
	// back_inserter ��� ũ�⸦ ������ ������ �־ �������.
	vector<int> v{  1,2,3 };
	vector<int> v2{ 2,3,4 };
	vector<int> v3;
	vector<int> v4;
	vector<int> v5;

	merge(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v3));
	for (auto i : v3) cout << i << " ";
	cout << "\n";
	// *** set_intersection : �� ������ �����տ� �ش��ϴ� ���Ҹ� �����´�. (set-theory ������)
	set_intersection(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v4)); // v4 : 2, 3
	for (auto i : v4) cout << i << " ";
	cout << "\n";
	// *** set_union(): �� ���ĵ� ������ ���ϵ�, �ߺ��� ��Ҵ� �����Ѵ�.
	set_union(cbegin(v), cend(v), cbegin(v2), cend(v2), back_inserter(v5)); // 1. 2. 3. 4;
	for (auto i : v5) cout << i << " ";

}