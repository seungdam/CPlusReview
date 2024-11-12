#include "pch.h"

// unordered_associative_container ==> hash_table�� ����Ѵ�.
// hash_table : �ε����� �������� �����Ǿ� �ִ�.
// key ���� hash func�� ���� �ؽ��� ���� �ε����� Ȱ���ϰ� �׿� ���� value���� ���Ͽ� ��� ���̴�.
// �ؽð��� ���� �ٷ� �ε����� �����ϹǷ� �� �����ڰ� �ƴ� �׵� �����ڸ� Ȱ���Ѵ�.
// ���� key���� �ش��ϴ� Ÿ���� �׵� �����ڸ� �����ؾ��Ѵ�.
// �׸��� �׿� �´� Hash �Լ� ���� �����ؾ��Ѵ�. (����� ���� Ŭ������ ���.. ) Ex) std::hash<T>

// �ٸ� Ű���� ���ؼ� ������ �ؽð��� �����ȴٸ� �ؽ� �浹�� �Ͼ �� �ִ�.
// forward iterator�� �̵��� �ܹ��⸸ �����ȴ�. rbegin/end�Ұ���

// unordered multimap/set�� ���� lower_bound upper_bound�� �������� ������ equal_range�� �����Ѵ�.

// 
using namespace std;

int main()
{
	unordered_map<string, int> um;
	unordered_multimap<string, int> umm;

	um.insert( {"Grams",10});
	um.insert( {"Grams",20 }); // doesn't work
	um.insert( {"Grams",30 });
	um["Grams"] = 100; // works;

}