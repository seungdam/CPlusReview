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
	// �ش� ������ ���� ������ �ڹٲ۴�. �翬�ϰԵ� const iterator�� ������ �־ x
	// value���� ������ x ���������� swap�� ȣ����
	// _copy ������ ����

	auto v{ vector<int>{1,2,3,4} };
	auto v2{ vector<int>{} };

	reverse(begin(v), end(v));
	reverse_copy(cbegin(v), cend(v), back_inserter(v2));
	print(v);
	print(v2);

	// *** rotate(begin, pivot, end)
	// advance�� �Բ� Ȱ��ȴ�.
	// pivot�� �ش��ϴ� ������ begin�� ������ ���� ������ ȸ����Ų��.
	
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
	// _copy ������ �����ϳ�, back_inserter�� Ȱ���� �� ������ �����ؾ���

}