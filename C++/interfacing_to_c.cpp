#include "pch.h"

#ifdef __cplusplus
extern "C" { 
#include "func.h"
}
#else
#include "func.h"
#endif


// 1. db api
// 2. os api
// 3. third-party lib & framework
// 4. language with foreign function interface
//   �� �ٸ� ���� ������ ����� �Լ��� C�� ���ؼ� �����س��� ��.
//   �� ��? ���̽��� ���� c���� ���� �����ս��� �����ֱ� ����


// Code Compatibility �ڵ� ȣȯ��
// C��� ���α׷��� legal C++ ���α׷����� ȣĪ�ϴ� ���� ������. ��? C�� C++����� subset�̱� ����
// ������ �� ���� �Ұ����ϴ�. C���� C++�� ����� �������� �ʱ� ����

// C99������ �Ϻ� ȣȯ���� ���� Ư���� �����ϱ� �Ѵ�. (designated initializer��� ���� �ִµ� 
// C++�� ��� C++20���� �����Ѵ�.)


// ���� ���� ���Ǵ°�? Binary Comatibility
// C++�� ���� ������ ���̺귯���� C��� ��� ���̳ʸ� ���Ͽ��� Ȱ���Ѵٸ�
// 1. ���ӽ����̽�
// 2. Ŭ����
// ���� ����� �߷��� �Ұ����ϴ�.
// �׷��� ������ �׻� ���� ���ӽ����̽��� ��Ʈ�� Ÿ������ �̷���� struct���� Ȱ���� �����ؾ��Ѵ�.

// �׸��� extern "C" �� �ٿ� ��� ��� ��ݿ��� Ȱ���� �Լ� ���� ��ø� ������Ѵ�.
// �̴� �����Ϸ��� Name Mangling�� �����ϱ� �����̴�.

//  ���� �̷��� C/C++���� ȣȯ���� �����ϱ� ���� interface�� �� ���� ��� Ȱ���� �� �־���ϸ�,
// ���� �ٸ� �� ���� ������ ��� �����ؾ��Ѵ�.

// �̶� C++�� ������ ���������� C�� ��� C++ ������ �������� �� C��� �����Ͽ� ������ �߻��� �� �����Ƿ�
// C++ ������ �Լ��� ���ܾ��Ѵ�. �̷��� �۾��� Conditional Compilation�̶�� ���´´�.

// #ifdef __cplusplus ...  ==> exclude from C Language Compiler

int main()
{
	std::vector<int> v{ 1,2,3,4,5 };
	print_arr(v.data(), v.size());
	std::map<int, int> m;
	m.insert({1,1});
	std::vector<MyPair> v2;
	for (auto [key,value] : m)
	{
		v2.push_back({ key,value });
	}
	print_map(v2.data(), v2.size());
}

// *** resource management
// c : malloc, free ==> no raii, no smart ptr, should make tidy-up function
// c++: new delete

// �ش� ���ҽ��� ���õ� ���� ������ �о�� ���� �߿��ϴ�.