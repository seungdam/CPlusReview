#include "pch.h"

using namespace std;

int main()
{

	// *** std::remove(range, value); return iterator of first removed elements.
	//  실제로 해당 원소를 제거하지 않는다. 즉, 컨테이너에 해당 원소는 그대로 남아있다. 
	// 다만 논리적인 의미로써 제거한다.
	// 제거 대상이 된 원소는 컨테이너의 맨 뒤로 이동하며 해당 값은 더 이상 정의된 값이 아니다.
	// 접근하려한다면 예상치 못한 동작을 수행한다.
	// 실제로 제거하려면 컨테이너의 erase를 호출해야한다.

	// 원소를 실제로 제거하는 것이 아니기 때문에 size()는 동일하다.

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

	// remove_copy : 원본을 유지하되 제거된 버전을 나타내는 새로운 배열에 할당
	remove_copy(cbegin(src), cend(src), back_inserter(dest), 1); // 1 을 제거한 버전
	remove_copy_if(cbegin(src), cend(src), back_inserter(dest), [](auto n) { return n % 3 == 0; }); // 3의 배수를 제거한 버전

	// dest 3 4 5 9 1 4 1 5

	for (auto i : dest) cout << i << " ";
	cout << "\n";

	/* copy_if version
	copy_if(cbegin(src),cend(src),back_inserter(dest), [](auto n) { return n != 1;})
	*/


	// *** std::unqiue(range, +@predicate); return first iterator of dulicated element.
	// 중복된 원소들을 remove한다. 앞서 언급했듯 논리적으로 삭제하는 것이지
	// 실제로 삭제하진 않는다. 컨테이너 멤버 함수로 구현된 unique를 수행하면 물리적으로도 제거해준다.
	// predicate(auto prev, auto current) 이전 원소와 현재 원소를 인자로 넘겨준다.


	// 얘도 마찬가지로 unique_copy 버전이 존재한다.
}