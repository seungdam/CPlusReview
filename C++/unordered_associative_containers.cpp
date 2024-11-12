#include "pch.h"

// unordered_associative_container ==> hash_table을 사용한다.
// hash_table : 인덱스와 버켓으로 구성되어 있다.
// key 값을 hash func을 통해 해싱한 값을 인덱스로 활용하고 그에 관한 value값을 버켓에 담는 것이다.
// 해시값을 통해 바로 인덱스에 접근하므로 비교 연산자가 아닌 항등 연산자를 활용한다.
// 따라서 key값에 해당하는 타입은 항등 연산자를 지원해야한다.
// 그리고 그에 맞는 Hash 함수 또한 지원해야한다. (사용자 정의 클래스의 경우.. ) Ex) std::hash<T>

// 다른 키값에 관해서 동일한 해시값이 생성된다면 해시 충돌이 일어날 수 있다.
// forward iterator의 이동이 단방향만 지원된다. rbegin/end불가능

// unordered multimap/set에 관해 lower_bound upper_bound는 지원하지 않지만 equal_range는 지원한다.

// 
using namespace std;

int main()
{
	unordered_map<string, int> um;
	unordered_multimap<string, int> umm;

	um.insert( {"Grams",10});
	um.insert( {"Grams",20 }); // doesn't work
	um.insert( {"Grams",30 });
	um["Grams"] = 100; // works;

}