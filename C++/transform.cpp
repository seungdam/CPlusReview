#include "pch.h"
#include <numeric>
#include <format>
using namespace std;

int main()
{
	auto v{ vector<int>(10,0) };
	iota(v.begin(), v.end(), 1);

	auto v2{vector<int>{}};
	auto v3{ vector<int>(v.size()) };
	auto v4{ vector<int>{} };

	// *** std::transform(src-range,dest,predicate)
	transform(cbegin(v), cend(v), back_inserter(v2), [](auto n) { return n * n; });
	transform(cbegin(v), cend(v), begin(v3), [](auto n) { return n * 2; });
	transform(cbegin(v), cend(v), begin(v), [](auto n) {return n * 100; });
	cout << " v: ";
	for (auto i : v) cout << format("{:04}", i) << " ";
	cout << "\nv2: ";
	for (auto i : v2) cout << format("{:04}",i) << " ";
	cout << "\nv3: ";
	for (auto i : v3) cout << format("{:04}", i) << " ";

	// *** transform(src-range1,src-range2, dest, predicate)
	// 원소의 개수가 동일한 두 range를 활용해 transform 하는 것도 가능하다.

	transform(cbegin(v), cend(v), cbegin(v2), back_inserter(v4), [](auto n, auto n2) {  return n + n2; });
	cout << "\nv4: ";
	for (auto i : v4) cout << format("{:04}", i) << " ";

}