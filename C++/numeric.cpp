#include "pch.h"
#include <numeric>
#include <execution>


using namespace std;

int main()
{
	vector<int> num(100, 0);
	std::iota(num.begin(), num.end(), 1); // 1~ ���������� �迭�� ä���ش�.

	auto sum = 0;
	sum = std::accumulate(num.cbegin(), num.cend(), sum); // �����հ踦 ���Ѵ�.
	// �̶� ��� ������ ���������� ó���ȴ�. ���� ó�� X

	// C++17�� reduce�� accumulate�� ����ó�� ����� �߰��� Ȯ�� �����̴�.
	sum = 0;
	sum = std::reduce(std::execution::par, num.cbegin(), num.cend(), sum);

	cout << sum << "\n";


}