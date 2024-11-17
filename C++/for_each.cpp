#include "pch.h"

using namespace std;

int main()
{

	// *** for-each: �����̳��� ��� ��ҿ� ���� predicate�� ����
	 
	auto str{ "hello world"s };

	for_each(str.begin(), str.end(), [](auto& c) { c = toupper(c); cout << c; }); // HELLO WORLD

	for (auto& i : str)
	{
		i = tolower(i);
	}
	// ��� for_each�� ����� range-for loop�� ���� ǥ���� �� ����.
	// for_each�� C++98���� �����ϴ� ����̰� range-for loop�� C++11���� ������ ����
	// ��� range-for loop�� ����ϴ� ���� �� �����ϴ�.
	// �߰��� �ݺ����� ������ �� �� �ֱ� �����̴�.


	// ������ Ư���� ���� for_each�� ���� �����ϱ⵵ �ϴ�.
	// ��ü�� �ƴ� �Ϻ� ������ ���� ����� ������ ��� for_each�� �� ����.
	// Ȥ�� ���� ������� ���ο� �������� �ʴ� �ֽ� ����� ���� ��, for_each�� Ȱ���� �� �ִ�.
	// for-each ���� ���������� ����ó�� ������ �����Ѵ�.
}