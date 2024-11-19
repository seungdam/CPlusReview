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
	vector<student> s{ {"john smith's",100},{"john jame's",30}, {"john smith's", 50}, {"john jame's", 10}, {"john jame's", 50} };

	// sort : 불완전 정렬(동일한 키에 관해 이후 원소의 정렬이 불완전 하다.)
	sort(begin(s), end(s));
	for (auto i : s) cout << i.name << " " << i.id << "\n";
	cout << "\n\n";

	// stable_sort : 완전 정렬 (동일한 키에 관해 원소의 정렬이 완전)
	stable_sort(begin(s), end(s));
	for (auto i : s) cout << i.name << " " << i.id << "\n";

	// is_sorted : 정렬된 컨테이너인지 확인
	// is_sorted_until: 정렬되지 않은 첫 원소 지점을 찾아 iterator를 반환


	// 부분만 정렬하는 기능도 있음
	
	// partial_sort(begin,pivot, end)
	// pivot = begin + n ==> n 개수만큼 정렬
	// 당연히 완전 정렬보다 속도도 빠름

	// _copy 버전도 존재함

	string str{"qwertyuiopasdfghjklzxcvbnm"};
	// partial_sort(begin(str),begin(str) + 5, end(str)); // 5개까지만 정렬 abcde
	// cout << str.substr(0, 5);


	// nth_element : 가져오고자 하는 n번째 랭크값까지 파티셔닝을 수행한다.
	nth_element(begin(str), begin(str) + 4, end(str)); // 5번째 정렬값
	for (auto i : str) cout << i;
}