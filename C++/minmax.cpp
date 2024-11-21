#include "pch.h"
#include <numeric>
using namespace std;


int main()
{
	string a{ "abcfee" };
	string b{ "defg" };
	auto minValue = min(a, b, [](auto& a, auto& b) {return a.length() < b.length(); });
	auto maxValue = max(a, b, [](auto& a, auto& b) {return a.length() < b.length(); });

	cout << minValue << " " << maxValue;


	auto max_init = max({ "a","b","c" });
	auto min_init = min({ "a","b","c" });

	auto [min, max] = minmax({ "a","b","c" }); // give pair structures..

	// min_element max_element(range) ==> return the iterator of min/max value
	// minmax_element ==> return pair iterator of [min, max] value


	// *** <cmath> << ������ ���� �Լ����� �ټ� �����ϰ� �����Ƿ� ��ǥ���� ���� �����ϴ�.

}