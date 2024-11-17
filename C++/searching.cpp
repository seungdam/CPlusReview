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
	// vowels �� ���� �ܾ� �� �ش� ���忡�� �߰ߵǴ� ù��° ������ ��ȯ
	// 
	while (vowel != cend(str))
	{
		cout << "find " << *vowel << " from index:" << distance(cbegin(str), vowel) << "\n";
		vowel = find_first_of(next(vowel), cend(str), cbegin(vowels), cend(vowels));
	}

	auto str2{ "Hellow World"s };
	auto adj = adjacent_find(cbegin(str2), cend(str2));

	// ������ ���� ������ ��� �� ������ ��ġ�� ��ȯ
	if (adj != cend(str2)) cout << "find adj elements " << *adj << " from index: " << distance(cbegin(str2), adj) << "\n";


	auto nums{ vector<int>(5,0) };
	::iota(begin(nums), end(nums), 1);
	nums[3] = 5;
	nums[2] = 5; // 1 2 5 5 5

	auto n = search_n(cbegin(nums), cend(nums), 3, 5);
	if (n != cend(nums)) cout << "found 3 elements with value 5 starting at index: " << distance(cbegin(nums), n) << "\n";

	auto substr{ "sd"s };
	// �� ���ͷ����� ������ ������, ���� Ž���� ��� �ڴ� �κ� Ž�� ����� ��Ÿ����.
	auto ret = search(cbegin(str), cend(str), cbegin(substr), cend(substr));
	if (ret != cend(str)) cout << "found sd from str in index: " << distance(cbegin(str), ret) << "\n";


	vector<int> range1{ 1,2,3,4,5 };
	vector<int> range2{ 1,2,2,4,5 };

	// �� ������ ���� ó�� mismatch�� ������ ��ġ�� ��ȯ
	auto [mr1, mr2] = mismatch(range1.cbegin(), range1.cend(), range2.cbegin(), range2.cend());

	cout << (mr1 - range1.cbegin()) << " : " << (mr2 - range2.cbegin()) << "\n";


	// *** OOO of series : return bool type
	// 1. all_of  (range, predicate) : ��� ���Ұ� predicate ���ǿ� �ش��ϸ� true
	// 2. any_of  (range, predicate) : �ϳ��� ���Ҷ� predicate ���ǿ� �ش��ϸ� true
	// 3. none_of (range, predicate) : ��� ���Ҷ� predicate ���ǿ� �ش����� �ʴٸ� true

	auto is_odd = [](auto n) {return n % 2 == 1; };
	cout << boolalpha << "all of odd: " << all_of(range1.begin(), range1.end(), is_odd) << "\n";
	cout << "any of odd: " << any_of(range1.begin(), range1.end(), is_odd) << "\n";
	cout << "none of odd: " << none_of(range1.begin(), range1.end(), is_odd) << "\n";


	// sorted ���� Ž�� �˰��� �Լ�
	
	// *** binary search(range, value) (feat. vs find)
	//  ���ĵ� �迭�̶�� �����Ͽ� binary search�� �ξ� ������. �翬�� ��
	// binary search�� sorted �� range�� �����Ͽ� Ȱ�밡��


	// *** include(range1, range2)
	// range1, range2 ��� ���ĵǾ����.
	// range1�ȿ� range2������ ��Ұ� ��� ���ԵǾ��ִ��� Ȯ��

}