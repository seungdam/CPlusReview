#include "pch.h"

using namespace std;

int main()
{
	// *** partitioning
	// �����̳ʾ��� ���ҿ� ���� Ư�� ������Ƽ�� �����ϴ� ���Ҹ� �տ� �� �ܿ��� �ڿ� ��ġ�ϴ� �˰����̴�.
	// Ex) �޴��� �޽��� ����� ������ ��, ������ �޽����� �ִ� ä�ù��� ������ �� �ܿ��� ������ ��ġ�ϴ� ��� Ȱ��
	// Ex) ���õ� �������� ���ʿ� �� �ܿ��� ���ʿ� ��ġ

	//    [a][b]    [c][d]
	//  property | !property
	//   partition points


	// *** partition(range, predicate);
	// ���⼭ predicate�� property�� �ش��Ѵ�.
	// �ش� predicate�� true�� ��ȯ�ϸ� front �ƴϸ� back�� ��ġ�Ѵ�.

	auto v{ vector<int>{3,1,4,1,5,9,2,8,1,6} };

	partition(begin(v), end(v), [&](auto n) { 
		return n % 2 == 1; 
		});
	std::cout << "UnStable Version: ";
	print(v);

	// stable version�� �Է� ������ �����ϴ� ������ ��ġ�� �����ش�.


	auto v2{ vector<int>{3,1,4,1,5,9,2,8,1,6} };
	stable_partition(begin(v2), end(v2), [](auto n) { 
		return n % 2 == 1; 
		});
	std::cout << "Stable-Version:   ";
	print(v2);

	//*** is_partition(range, predicate) : return bool ��Ƽ�Ŵ׵� �����̳����� ����� ��ȯ
	// partition_point('''') : ���� ��Ƽ�Ŵ��� �ȵ� �����̳��̶��, ���ʷ� ��Ƽ�Ŵ� �ؾ��ϴ� ������ ���ͷ����� ��ȯ
	// ��Ƽ�Ŵ��� �� �����̳ʶ�� ��Ƽ�Ŵ� ����Ʈ�� ��ȯ
	auto iter = partition_point(begin(v2), end(v2), [](auto n) {return n % 2 == 1;});
	std::cout << *iter << "\n";

}