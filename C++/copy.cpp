#include "pch.h"

using namespace std;

int main()
{
	// std::copy 특정 iterator range를 다른 곳으로 복사한다.
	// 보편적으로 sequenctial containers에 분포시키기 위해 활용된다.

	// std::copy (source range, destination);

	vector<int> v{ 1,2,3,4,5 };
	vector<int> dest(v.size());
	vector<int> ev;

	copy(cbegin(v), cend(v), dest); 
	copy(cbegin(v), cend(v), back_inserter(ev)); // for empty container;
	/* pseudo code
		for(const auto i : v)
		{
			ev.push_back(i);
		}
	*/


	// copy_n(range start, element count, destination) n만큼의 요소를 복사한다.

	// copy_if(range, dest, predicate) predicate에 만족하는 원소만 복사한다.

}