#include "pch.h"

using namespace std;

int main()
{

	// *** write algorithm �����̳� �� ��Ҹ� �����ϴ� �˰���
	// �翬�ϰԵ� cbegin/end�� �ȵȴ�.

	vector<int> v{ 1,2,3,4,5 };

	replace(v.begin(), v.end(), 1, 2); 
	// (range, target value, replace value);
	// target value�� replace value�� �����Ѵ�.
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

	// OOO_copy �Լ���
	// �ش� ������ �⺻ ������� �޸� �������� ������ �ʿ�� �� �� �����ϰ� Ȱ��ȴ�.
	// Ư�� ���� �����̳ʿ��� �����ϰ� Ȱ���� �� �ִ�.

	vector<int> v2;
	replace_copy(cbegin(v), cend(v), back_inserter(v2), 1, 2);
	for (auto i : v2) cout << i << " ";
	v2.resize(0);
	cout << "\n"; // v�� ������ �����ϵ�, �ش� ���ǿ� �°� ������ ���� ���ο� ���Ϳ� copy

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