#include "pch.h"
#include <list>
#include <forward_list>

using namespace std;

int main()
{
	forward_list<int> fl; // ������(�ܹ���) ����Ʈ

	for (int32 elm{ 0 }; elm < 10; ++elm) fl.push_front(elm);
	cout << "fl: ";

	for (auto& i : fl) cout << "[" << i << "] ";

	cout << "\n";
	auto end{ fl.begin() }; // fl.end() is point after last elm
	advance(end, 9); // so advance it // �������̶� -1ó�� sliding �Ұ���
	fl.insert_after(end, 10);
	cout << "fl: ";
	for (auto& i : fl) cout << "[" << i << "] ";
	std::cout << "\n";

	list<int> ll; // ����� ��Ʈ��
	for (int32 elm{ 0 }; elm < 10; ++elm) ll.push_back(elm);

	cout << "ll: ";
	for (auto& i : ll) cout << "[" << i << "] ";

	auto end2{ ll.end() }; // fl.end() is point after last elm
	advance(end2, -1);     //  ������̶� -1ó�� sliding ����
	ll.insert(end2, 10);   // �ش� iterator ���ʿ� �߰�
	ll.push_front(100);
	cout << "\ndl: ";
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.sort(greater<int>{}); // list�� random-access�� �ȵǼ� std::sort�� ���Ұ�. ��� ���� �Լ� ���
	
	cout << "sorted ll: "; 
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.remove(10);
	for (auto& i : ll) cout << "[" << i << "] ";
	cout << "\n";
	ll.remove(100);
	for (auto& i : ll) cout << "[" << i << "] ";

	// .remove(elm value) �ش� value�� ����
	// .remove_if()
	// .unique �ߺ� ��� ����
	// .reserve ���� ������

	// .merge(�� �ٸ� ����Ʈ) "���ĵ�" �� ����Ʈ�� �����Ѵ�. ������ ����Ʈ�� ���ĵ� ����

	list<int> l1{ 4,1,23 };
	list<int> l2{ 10,45,7 };

	l1.sort();
	l2.sort();
	l1.merge(l2); //l2 gonna be empty
	cout << "\n";
	for (auto& i : l1) cout << "[" << i << "] ";


	// insert vs insert_range(c++20) : ������ ����
	// .splice(where, list) ==> list�� range��ŭ�� ��Ҹ� where�� �߰��Ѵ�.
	// ==> insert(where, range)�� �ٸ����� ���簡 �ƴ� �̵��� ����ȴٴ� ��.
	list<int> l3{ 88,99,100 };

	auto second{ l1.begin() };
	advance(second, 1);
	l1.splice(second, l3);

	cout << "\n";
	for (auto& i : l1) cout << "[" << i << "] ";
}