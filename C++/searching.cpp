#include "pch.h"
#include <numeric>

using namespace std;

class functor
{
	bool operator()(auto a)
	{
		std::cout << a;
	}
};

int main()
{

	auto str{ "Hi my name is ohsd"s };
	auto vowels{ "aeiou"s };
	auto vowel = find_first_of(cbegin(str), cend(str), cbegin(vowels), cend(vowels));
	// vowels 에 속한 단어 중 해당 문장에서 발견되는 첫번째 지점을 반환
	// 
	while (vowel != cend(str))
	{
		cout << "find " << *vowel << " from index:" << distance(cbegin(str), vowel) << "\n";
		vowel = find_first_of(next(vowel), cend(str), cbegin(vowels), cend(vowels));
	}

	auto str2{ "Hellow World"s };
	auto adj = adjacent_find(cbegin(str2), cend(str2));

	// 동일한 값이 인접한 경우 그 마지막 위치를 반환
	if (adj != cend(str2)) cout << "find adj elements " << *adj << " from index: " << distance(cbegin(str2), adj) << "\n";


	auto nums{ vector<int>(5,0) };
	::iota(begin(nums), end(nums), 1);
	nums[3] = 5;
	nums[2] = 5; // 1 2 5 5 5

	auto n = search_n(cbegin(nums), cend(nums), 3, 5);
	if (n != cend(nums)) cout << "found 3 elements with value 5 starting at index: " << distance(cbegin(nums), n) << "\n";

	auto substr{ "sd"s };
	// 두 이터레이터 범위를 가지며, 앞은 탐색할 대상 뒤는 부분 탐색 대상을 나타낸다.
	auto ret = search(cbegin(str), cend(str), cbegin(substr), cend(substr));
	if (ret != cend(str)) cout << "found sd from str in index: " << distance(cbegin(str), ret) << "\n";


	vector<int> range1{ 1,2,3,4,5 };
	vector<int> range2{ 1,2,2,4,5 };

	// 두 범위에 관해 처음 mismatch된 원소의 위치를 반환
	auto [mr1, mr2] = mismatch(range1.cbegin(), range1.cend(), range2.cbegin(), range2.cend());

	cout << (mr1 - range1.cbegin()) << " : " << (mr2 - range2.cbegin()) << "\n";


	// *** OOO of series : return bool type
	// 1. all_of  (range, predicate) : 모든 원소가 predicate 조건에 해당하면 true
	// 2. any_of  (range, predicate) : 하나의 원소라도 predicate 조건에 해당하면 true
	// 3. none_of (range, predicate) : 어떠한 원소라도 predicate 조건에 해당하지 않다면 true

	auto is_odd = [](auto n) {return n % 2 == 1; };
	cout << boolalpha << "all of odd: " << all_of(range1.begin(), range1.end(), is_odd) << "\n";
	cout << "any of odd: " << any_of(range1.begin(), range1.end(), is_odd) << "\n";
	cout << "none of odd: " << none_of(range1.begin(), range1.end(), is_odd) << "\n";


	// sorted 전용 탐색 알고리즘 함수
	
	// *** binary search(range, value) (feat. vs find)
	//  정렬된 배열이라는 가정하에 binary search가 훨씬 빠르다. 당연한 것
	// binary search는 sorted 된 range에 한정하여 활용가능


	// *** include(range1, range2)
	// range1, range2 모두 정렬되어야함.
	// range1안에 range2범위의 요소가 모두 포함되어있는지 확인

}