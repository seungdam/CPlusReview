#include "pch.h"
#include <numeric>
#include <execution>


using namespace std;

int main()
{
	vector<int> num(10, 0);
	std::iota(num.begin(), num.end(), 1); // 1~ 순차적으로 배열을 채워준다.

	auto sum = 0;
	// accumulate(range, initial_value, +@ predicate or functor)
	sum = std::accumulate(num.cbegin(), num.cend(), sum); // 누적합계를 구한다.
	// 이때 모든 연산은 순차적으로 처리된다. 병렬 처리 X

	// C++17의 reduce는 accumulate의 병렬처리 기능이 추가된 확장 버전이다.
	sum = 0;
	sum = std::reduce(std::execution::par, num.cbegin(), num.cend(), sum);

	cout << sum << "\n";


	vector<int> partial;
	partial_sum(cbegin(num), cend(num), back_inserter(partial)); // 누적합을 순차적으로 나열
	// 1, 1+2, 1+2+3.... , 1+2+3 ... + 99 + 100

	for (auto i : partial) cout << i << " ";


	vector<int> adjcent_sub;
	adjacent_difference(cbegin(num), cend(num), back_inserter(adjcent_sub));
	// 인접한 원소간의 차이값을 나열한다.
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
	// 예를 들어 실험 결과에 관한 차이를 비교 분석 후, 이 중 오차가 가장 큰 결과를 탐색한다고 가정해보자.
	vector<int> expected{ 1,2,3,4,5 };
	vector<int> actual{ 2,4,1,3,10 };

	auto result = inner_product(cbegin(expected), cend(expected), cbegin(actual), 0.0,
		[](auto r1, auto r2) {return max(r1, r2); }, // accumulate part : using transform result directly
		[](auto e, auto a) {return fabs(a - e); } // transform part
	);

	cout << result << "\n";

	// C++17부턴 inner_product의 병럴처리 버전인 transform_reduce도 존재한다.


}