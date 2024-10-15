#include "pch.h"
#include <list>
#include <forward_list>

using namespace std;

int main()
{
	forward_list<int> fl; // 정방향(단방향) 리스트

	for (int32 elm{ 0 }; elm < 10; ++elm) fl.push_front(elm);
	cout << "fl: ";

	for (auto& i : fl) cout << "[" << i << "] ";

	cout << "\n";
	auto end{ fl.begin() }; // fl.end() is point after last elm
	advance(end, 9); // so advance it // 정방향이라 -1처럼 sliding 불가능
	fl.insert_after(end, 10);
	cout << "fl: ";
	for (auto& i : fl) cout << "[" << i << "] ";
	std::cout << "\n";

	list<int> ll; // 양방향 리트스
	for (int32 elm{ 0 }; elm < 10; ++elm) ll.push_back(elm);

	cout << "ll: ";
	for (auto& i : ll) cout << "[" << i << "] ";

	auto end2{ ll.end() }; // fl.end() is point after last elm
	advance(end2, -1);     //  양방향이라 -1처럼 sliding 가능
	ll.insert(end2, 10);   // 해당 iterator 앞쪽에 추가
	ll.push_front(100);
	cout << "\ndl: ";
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.sort(greater<int>{}); // list는 random-access가 안되서 std::sort는 사용불가. 대신 내장 함수 사용
	
	cout << "sorted ll: "; 
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.remove(10);
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.remove(100);
	for (auto& i : ll) cout << "[" << i << "] ";

	// .remove(elm value) 해당 value값 제거
	// .remove_if()
	// .unique 중복 요소 제거
	// .reserve 정렬 뒤집기

	// .merge(또 다른 리스트) "정렬된" 두 리스트를 병합한다. 병합한 리스트도 정렬된 상태

	list<int> l1{ 4,1,23 };
	list<int> l2{ 10,45,7 };

	l1.sort();
	l2.sort();
	l1.merge(l2); //l2 gonna be empty
	cout << "\n";
	for (auto& i : l1) cout << "[" << i << "] ";


	// insert vs insert_range(c++20) : 가독성 차이
	// .splice(where, list) ==> list의 range만큼의 요소를 where에 추가한다.
	// ==> insert(where, range)와 다른점은 복사가 아닌 이동이 수행된다는 점.
	list<int> l3{ 88,99,100 };

	auto second{ l1.begin() };
	advance(second, 1);
	l1.splice(second, l3);

	cout << "\n";
	for (auto& i : l1) cout << "[" << i << "] ";
}