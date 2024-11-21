#include "pch.h"

using namespace std;


int main()
{
	// *** write-only algorithm � ������� read�ϴ� ���� �ƴ� ���� ���⸸ �ϴ� �˰��� �Լ���

	vector<int> v(10);
	fill(v.begin(), v.end(), 42); // fill all element as 42

	auto iter = fill_n(v.begin(), 5, 10); // fill 5 element as 10 from begin and return next iterator
	fill(iter, v.end(), 99);

	// �ݵ�� ���ʹ� �� ���Ͱ� �ƴϿ����Ѵ�.
	for (auto i : v) cout << i << " ";
	cout << "\n";

	// back_inserter�� Ȱ���� �� ���Ϳ����� Ȱ�밡��
	vector<int> ev;
	auto iter2 = fill_n(back_inserter(ev), 5, 42);

	generate(v.begin(), v.end(), [n = 0]() mutable {++n; return n * n; });
	generate_n(back_inserter(ev), 5, [n = 10]() mutable {++n; return n * n; });
	for (auto i : v) cout << i << " ";
	cout << "\n";
}