#include "pch.h"

using namespace std;

struct student
{
	string name;
	int id;
	bool operator<(const student& rhs) const { return name < rhs.name; }
	
};

int main()
{
	vector<student> s{ {"john smith's",0},{"john jame's", 1}, {"john smith's", 2}, {"john jame's", 3}, {"john jame's", 4} };

	// sort : �ҿ��� ����(������ Ű�� ���� ���� ������ ������ �ҿ��� �ϴ�.)
	sort(begin(s), end(s));
	for (auto& [name, id] : s) cout << name << " " << id << "\n";
	cout << "\n\n";

	// stable_sort : ���� ���� (������ Ű�� ���� ������ ������ ����)
	stable_sort(begin(s), end(s));
	for (auto &[name, id] : s) cout << name << " " << id << "\n";

	// is_sorted : ���ĵ� �����̳����� Ȯ��
	// is_sorted_until: ���ĵ��� ���� ù ���� ������ ã�� iterator�� ��ȯ


	// �κи� �����ϴ� ��ɵ� ����
	
	// partial_sort(begin,pivot, end)
	// pivot = begin + n ==> n ������ŭ ����
	// �翬�� ���� ���ĺ��� �ӵ��� ����

	// _copy ������ ������

	string str{"qwertyuiopasdfghjklzxcvbnm"};
	// partial_sort(begin(str),begin(str) + 5, end(str)); // 5�������� ���� abcde
	// cout << str.substr(0, 5);


	// nth_element : ���������� �ϴ� n��° ��ũ������ ��Ƽ�Ŵ��� �����Ѵ�.
	nth_element(begin(str), begin(str) + 4, end(str)); // 5��° ���İ�
	for (auto i : str) cout << i;
}