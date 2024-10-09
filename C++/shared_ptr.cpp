#include "pch.h"

// *** shared_ptr ==> ���� ��ü�� ����Ű�� Pointer 
//					  + Ref Counting �� ��Ÿ�۾��� �����ϴ� Control Block���� �̷����.


// 1. ��ü�� �ּҸ� �����ڿ� �Ѱ� �ʱ�ȭ�ϱ� ����.
// 2. make_shared()�� ���� �ʱ�ȭ �ϴ� �͵� ����.
// 3. unique_ptr ��ü�� shared_ptr ��ü�� ��ȯ ����. �׿��� �ȵ�.
// 4. pointer vs unique_ptr --> ���� ��
// 5. unique_ptr vs shared_ptr --> shared_ptr�� ref-counting �� ��Ʈ�� ����� ������� ���� ������尡 ��ŭ..
// �׷��� ������ � ��ü�� �����ؾ��ϴ� ��Ȳ������ Ȱ���ϴ� ���� ����. �� �ܿ��� unique_ptr�� �н�.
// 6. shared_ptr�� ����,�̵� ������ü�� atomic������ ������ ������ atomic ���� ����. c++20���ʹ� atomic shared pointer�� ����.
int main()
{
	std::shared_ptr<int> sptr{ new int{42} }; // ��ü�� �ּҸ� �ѱ��
	auto sptr2{ std::make_shared<int>(42) }; // make_shared ����ϱ�
	std::cout << sptr.use_count() << "\n";
	auto csptr = sptr; // copy cons   ref-cnt 1
	std::cout << sptr.use_count() << "\n";
	sptr2 = sptr; // copy assign ref-cnt 2  sptr2 ref-cnt = 0;
	std::cout << sptr.use_count() << "\n";
	auto msptr = std::move(sptr);
	std::cout << "after move: " << csptr.use_count() << "\n";
	msptr = nullptr; // release
	std::cout << csptr.use_count() << "\n";

}