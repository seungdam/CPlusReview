#include "pch.h"

using namespace std;

int main()
{
	// *** partitioning
	// 컨테이너안의 원소에 관해 특정 프러퍼티를 만족하는 원소를 앞에 그 외에는 뒤에 배치하는 알고리즘이다.
	// Ex) 휴대폰 메시지 목록을 보여줄 때, 안읽은 메시지가 있는 채팅방을 상위에 그 외에는 하위에 배치하는 등에서 활용
	// Ex) 선택된 아이템을 앞쪽에 그 외에는 뒤쪽에 배치

	//    [a][b]    [c][d]
	//  property | !property
	//   partition points


	// *** partition(range, predicate);
	// 여기서 predicate가 property에 해당한다.
	// 해당 predicate가 true를 반환하면 front 아니면 back에 배치한다.

	auto v{ vector<int>{3,1,4,1,5,9,2,8,1,6} };

	partition(begin(v), end(v), [&](auto n) { 
		return n % 2 == 1; 
		});
	std::cout << "UnStable Version: ";
	print(v);

	// stable version은 입력 순서를 보장하는 완전한 배치를 보여준다.


	auto v2{ vector<int>{3,1,4,1,5,9,2,8,1,6} };
	stable_partition(begin(v2), end(v2), [](auto n) { 
		return n % 2 == 1; 
		});
	std::cout << "Stable-Version:   ";
	print(v2);

	//*** is_partition(range, predicate) : return bool 파티셔닝된 컨테이너인지 결과를 반환
	// partition_point('''') : 만약 파티셔닝이 안된 컨테이너이라면, 최초로 파티셔닝 해야하는 원소의 이터레이터 반환
	// 파티셔닝이 된 컨테이너라면 파티셔닝 포인트를 반환
	auto iter = partition_point(begin(v2), end(v2), [](auto n) {return n % 2 == 1;});
	std::cout << *iter << "\n";

}