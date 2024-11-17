#include "pch.h"
#include <numeric>
#include <execution>


using namespace std;

int main()
{
	vector<int> num(100, 0);
	std::iota(num.begin(), num.end(), 1); // 1~ 순차적으로 배열을 채워준다.

	auto sum = 0;
	sum = std::accumulate(num.cbegin(), num.cend(), sum); // 누적합계를 구한다.
	// 이때 모든 연산은 순차적으로 처리된다. 병렬 처리 X

	// C++17의 reduce는 accumulate의 병렬처리 기능이 추가된 확장 버전이다.
	sum = 0;
	sum = std::reduce(std::execution::par, num.cbegin(), num.cend(), sum);

	cout << sum << "\n";


}