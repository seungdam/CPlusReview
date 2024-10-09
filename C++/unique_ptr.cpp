#include "pch.h"
#include <memory>

// Memory Leak
// Dangling Pointer
// �� �� ������ �������� �Ҵ��� �޸𸮸� �����ϴ� �Ϳ� �־ ������� ������ ��� ���
// �߻��� �� �ִ� �پ��� �������� �����ϱ� ���� ������ ����Ʈ ������
// *** ���� ���ε����� Ȱ�� ����


//  Smart Pointer�� �Ҵ�� �޸𸮸� ĸ��ȭ�� Wrapper Class

// 1. ���� public M.F�� ���� ���ٸ��� ���ȴ�.
// 2. RAII ������� �����Ǿ� �ִ�.
// 3. ���� ����� ���õ� �̽��� �߻����� �ʴ´�.
// 4. �����͸� ����ų� ��ȿȭ ��ų �� ����.

// *** unique_ptr --> auto_ptr�� ��������(auto_ptr ���� ��� move semantic�� �������� �ʾ���.)
// ����, �Ҵ��� �Ұ��������� �̵��� �����ϴ�.
// 1. ��κ��� Heap Memory �Ҵ� ��Ȳ���� �����ϰ� ����� �����ϴ�.
// 2. ������ ������ Ŭ������. => ������尡 ���� ������, �Ϲ����� �����͸� ����ϴ� �Ͱ� �ٸ��� ����.
// 3. ���ø� Ŭ������, �츮�� ��� Ȱ���ϴ� �⺻ �����͸� ����� ������ ������, �Ϻ� ���� ��� ���� �����ȴ�.
// 4. ���ø� ���ڷδ� �Ҵ��� �������� Ÿ���� ����. unique_ptr<int> uptr ==> int*
// 5. move-only class�̴�.

// *** shared_ptr --> shared_ptr���� ������ �����ϴ�. Ref Counting�̶�� ����� ä���� �����Ѵ�.

// �� ��� ��� �����ϴµ� �ð��� ���� �ҿ�Ǳ� ������ �ʿ��� ��Ȳ���� Ȱ���ϴ� ���� ����.
struct Pos
{
	int x;
	int y;
};


void func(std::unique_ptr<Pos> uptr)
{
	std::cout << "Pass " << uptr << " to function.\n";
}

std::unique_ptr<Pos> make_unique_pos(int x, int y)
{
	Pos p{ x,y };
	auto upptr{ std::make_unique<Pos>(p) };
	return upptr; // ������ �����Ϸ��� move ����ȭ�� �����ϹǷ� ���� std::move�� ���� �ʿ�� ����.
}

int main()
{
	// C++11
	std::unique_ptr<int> uptr1{ new int{42} }; // new ������ �Բ� Ȱ��ȴ�.
	std::unique_ptr<int[]> uptr2{ new int[6] }; // fixed-size-array ���� ���� �迭 ���� ������ �� �ִ�.

	// C++14
	// C++14���ʹ� make_pair�� ���� make_unique ���̺귯�� �Լ��� ����. 
	// �翬�� perfect-forwarding�� �����Ѵ�.
	auto uptr3{ std::make_unique<int>(42) };
	auto uptr4{ std::make_unique<int[]>(6)};

	std::cout << "uptr1: " << uptr1 << " *uptr1: " << *uptr1 << "\n"; // ������ ����
	std::cout << "uptr2[0]: " << uptr2[0] << "\n"; // �迭�� �ε����� ���� ���� ����
	// std::cout << *uptr2; ==> Error �迭 ��ü�� ������ �Ұ����ϴ�.
	// ++ -- �� ���� �������굵 �Ұ���
	// uptr1 = uptr2 �� ���� copy assign / copy constructor ȣ�⵵ �Ұ��� ... ���� move�� ����

	std::unique_ptr<int> uptr5{ std::move(uptr1)};
	uptr1 = nullptr; // nullptr�� �����ϸ� ���� �Ҵ�� �޸𸮴� �����ȴ�.
	std::cout << "*uptr1: " << uptr1 << "\n";
	std::cout << "*uptr5: " << uptr5 << "\n";


	auto pos_uptr{ std::make_unique<Pos>(Pos{10,10}) };
	std::cout <<"pos_uptr: " << pos_uptr << " X: " << pos_uptr->x << " Y: " << pos_uptr->y << "\n";
	func(std::move(pos_uptr));

	std::cout << make_unique_pos(3, 6)->x;
} 