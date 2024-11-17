#include "pch.h"

using namespace std;

int main()
{
	// std::copy Ư�� iterator range�� �ٸ� ������ �����Ѵ�.
	// ���������� sequenctial containers�� ������Ű�� ���� Ȱ��ȴ�.

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


	// copy_n(range start, element count, destination) n��ŭ�� ��Ҹ� �����Ѵ�.

	// copy_if(range, dest, predicate) predicate�� �����ϴ� ���Ҹ� �����Ѵ�.

}