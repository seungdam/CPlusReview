#include "pch.h"


// *** algorithm with predicate
// �˰����� �� ��Ҹ��� bool ���� �����ϴ� �Լ��� ȣ���Ѵ�.
// �̷��� �Լ����� predicate��� ���´´�.

// ���� ���, std::find�� ��� == operator�� ���� target�� ã�Ƴ���.
// �� ��� == operator�� ȣ���� �� �ִ� callable object�� predicate�� �Ѱ��� �� �ִ�.
// std::sort�� ��� < operator�� ȣ���� �� �ִ� callable object (less , greater)�� predicate�� �Ѱ��� �� �ִ�.

using namespace std;

bool mysortpredicate(const string& lhs, const string& rhs)
{
	if (lhs.size() == rhs.size()) return lhs < rhs;
	return lhs.size() < rhs.size();
}

int main()
{
	unordered_set<int> us;
	us.insert(100);
	us.insert(290);
	int target = 100;
	auto iter = std::find(begin(us), end(us), 100);
	cout << *iter << "\n";

	vector<string> strs{ "hello","world","abc", "def", "hij" };

	std::sort(begin(strs), end(strs));
	for (auto s : strs) cout << s << " ";
	cout << "\n";
	std::sort(begin(strs), end(strs), greater<string>());
	for (auto s : strs) cout << s << " ";
	cout << "\n";
	std::sort(begin(strs), end(strs), mysortpredicate);
	for (auto s : strs) cout << s << " ";
}