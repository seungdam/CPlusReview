#include "pch.h"
#include <numeric>
#include <execution>


using namespace std;

int main()
{
	vector<int> num(10, 0);
	std::iota(num.begin(), num.end(), 1); // 1~ ���������� �迭�� ä���ش�.

	auto sum = 0;
	// accumulate(range, initial_value, +@ predicate or functor)
	sum = std::accumulate(num.cbegin(), num.cend(), sum); // �����հ踦 ���Ѵ�.
	// �̶� ��� ������ ���������� ó���ȴ�. ���� ó�� X

	// C++17�� reduce�� accumulate�� ����ó�� ����� �߰��� Ȯ�� �����̴�.
	sum = 0;
	sum = std::reduce(std::execution::par, num.cbegin(), num.cend(), sum);

	cout << sum << "\n";


	vector<int> partial;
	partial_sum(cbegin(num), cend(num), back_inserter(partial)); // �������� ���������� ����
	// 1, 1+2, 1+2+3.... , 1+2+3 ... + 99 + 100

	for (auto i : partial) cout << i << " ";


	vector<int> adjcent_sub;
	adjacent_difference(cbegin(num), cend(num), back_inserter(adjcent_sub));
	// ������ ���Ұ��� ���̰��� �����Ѵ�.
	cout << "\n";
	for (auto i : adjcent_sub) cout << i << " ";
	// 1 2 3  --> 1 - 1 = 0, 2 - 1, 3- 2

	vector<int> m1{ 1,2,3 };
	vector<int> m2{ 4,5,6 };
	// 1. inner_product(range1, range2, inital_value)
	auto scalar_product = inner_product(begin(m1), end(m1), begin(m2), 0);
	// 1*4 + 2*5 + 3*6 = 32

	// 1-1. inner_product ==> transform logic(such as multiply) + accumulate logic
	vector<int> rm;
	transform(cbegin(m1), cend(m1), cbegin(m2), back_inserter(rm), multiplies<int>{});
	auto scalar_product2 = accumulate(cbegin(rm), cend(rm), 0);

	cout << "\n" << scalar_product << " " << scalar_product2 << "\n";

	// 2. inner_product overloading version
	// inner_product(range1,range2,intial_value, predicate1(accumulate),predicate2(transform));
	// ���� ��� ���� ����� ���� ���̸� �� �м� ��, �� �� ������ ���� ū ����� Ž���Ѵٰ� �����غ���.
	vector<int> expected{ 1,2,3,4,5 };
	vector<int> actual{ 2,4,1,3,10 };

	auto result = inner_product(cbegin(expected), cend(expected), cbegin(actual), 0.0,
		[](auto r1, auto r2) {return max(r1, r2); }, // accumulate part : using transform result directly
		[](auto e, auto a) {return fabs(a - e); } // transform part
	);

	cout << result << "\n";

	// C++17���� inner_product�� ����ó�� ������ transform_reduce�� �����Ѵ�.


}