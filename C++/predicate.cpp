#include "pch.h"


// *** algorithm with predicate
// 알고리즘은 각 요소마다 bool 값을 리턴하는 함수를 호출한다.
// 이러한 함수들을 predicate라고 일컫는다.

// 예를 들어, std::find의 경우 == operator를 통해 target을 찾아낸다.
// 이 경우 == operator를 호출할 수 있는 callable object를 predicate로 넘겨줄 수 있다.
// std::sort의 경우 < operator를 호출할 수 있는 callable object (less , greater)를 predicate로 넘겨줄 수 있다.

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