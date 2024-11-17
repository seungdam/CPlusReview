#include "pch.h"

using namespace std;

int main()
{

	// *** std::remove(range, value); return iterator of first removed elements.
	//  ������ �ش� ���Ҹ� �������� �ʴ´�. ��, �����̳ʿ� �ش� ���Ҵ� �״�� �����ִ�. 
	// �ٸ� ������ �ǹ̷ν� �����Ѵ�.
	// ���� ����� �� ���Ҵ� �����̳��� �� �ڷ� �̵��ϸ� �ش� ���� �� �̻� ���ǵ� ���� �ƴϴ�.
	// �����Ϸ��Ѵٸ� ����ġ ���� ������ �����Ѵ�.
	// ������ �����Ϸ��� �����̳��� erase�� ȣ���ؾ��Ѵ�.

	// ���Ҹ� ������ �����ϴ� ���� �ƴϱ� ������ size()�� �����ϴ�.

	vector<int> num{1, 1, 1, 2, 2, 3, 3, 4, 5};
	auto iter = remove(begin(num), end(num), 1);
	//[2][2][3][3][4][5][?][?][?]
	cout << "original: ";
	for (auto i : num) cout << i << " ";
	cout << "\n";

	cout << "first-iterator of removed one: ";
	for (auto i = iter; i != num.end(); ++i) cout << *i << " "; // undefined-behavior
	cout << "\n";

	cout << "after call erase(): ";
	num.erase(iter, end(num));
	for (auto i : num) cout << i << " ";
	cout << "\n";
	


	vector<int> src{ 3,1,4,1,5,9 };
	vector<int> dest;
	// remove_if : using predicate

	// remove_copy : ������ �����ϵ� ���ŵ� ������ ��Ÿ���� ���ο� �迭�� �Ҵ�
	remove_copy(cbegin(src), cend(src), back_inserter(dest), 1); // 1 �� ������ ����
	remove_copy_if(cbegin(src), cend(src), back_inserter(dest), [](auto n) { return n % 3 == 0; }); // 3�� ����� ������ ����

	// dest 3 4 5 9 1 4 1 5

	for (auto i : dest) cout << i << " ";
	cout << "\n";

	/* copy_if version
	copy_if(cbegin(src),cend(src),back_inserter(dest), [](auto n) { return n != 1;})
	*/


	// *** std::unqiue(range, +@predicate); return first iterator of dulicated element.
	// �ߺ��� ���ҵ��� remove�Ѵ�. �ռ� ����ߵ� �������� �����ϴ� ������
	// ������ �������� �ʴ´�. �����̳� ��� �Լ��� ������ unique�� �����ϸ� ���������ε� �������ش�.
	// predicate(auto prev, auto current) ���� ���ҿ� ���� ���Ҹ� ���ڷ� �Ѱ��ش�.


	// �굵 ���������� unique_copy ������ �����Ѵ�.
}