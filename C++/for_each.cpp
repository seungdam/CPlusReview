#include "pch.h"

using namespace std;

int main()
{

	// *** for-each: 컨테이너의 모든 요소에 관해 predicate를 수행
	 
	auto str{ "hello world"s };

	for_each(str.begin(), str.end(), [](auto& c) { c = toupper(c); cout << c; }); // HELLO WORLD

	for (auto& i : str)
	{
		i = tolower(i);
	}
	// 사실 for_each의 기능은 range-for loop를 통해 표현할 수 있음.
	// for_each는 C++98부터 존재하던 기능이고 range-for loop는 C++11부터 등장한 것임
	// 사실 range-for loop를 사용하는 것이 더 좋긴하다.
	// 중간에 반복문을 종료할 수 도 있기 때문이다.


	// 하지만 특정한 경우는 for_each가 더욱 유용하기도 하다.
	// 전체가 아닌 일부 범위에 관해 기능을 수행할 경우 for_each가 더 낫다.
	// 혹은 아직 범위기반 루핑에 지원되지 않는 최신 기능이 있을 때, for_each를 활용할 수 있다.
	// for-each 또한 마찬가지로 병렬처리 버전이 존재한다.
}