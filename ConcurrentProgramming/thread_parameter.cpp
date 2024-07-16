#include "pch.h"

using namespace std;

void TaskCopy(int32 param)
{
	cout << "copy param :" << param << "\n";
}

void TaskRef(int32& lparam, int32&& rparam)
{
	cout << "l-ref param: " << lparam++   << "\n";
	cout << "r-ref param: " << rparam  << "\n";

}

template<typename... Tys> // template-parameter pack
void TaskVArg(Tys&&... params)
{
	cout << "varg param: ";
	(cout << ... << params); // fold expression <== C++17���� ������.
	cout << "\n";
}

int main()
{
	int32 a = 0;
	int32 b = 0;

	// *** thread�� ���� \
	\
	 thread�� �⺻������ ���ڸ� "����" ���·� �޾Ƶ��̸�, r/lvalue ref, �̵��� ���·� ���� �޴� �Ͷ��� �����ϴ�. \
	�̶� ref�� ���·� ���ڸ� �ִ� ���, ref ���·� �Ͻ��� ����ȯ�� ������� �ʱ� ������ �����ؾ��Ѵ�. \
	���� rvalue ������ ���� perfect forwarding�� �����Ѵٰ� �Ѵ�. 

	thread copy_thread(TaskCopy, a);
	copy_thread.join();

	thread ref_thread(TaskRef, std::ref(a), std::move(b));
	ref_thread.join();
	
	cout << "a: " << a << "\n"; // 1
	cout << "b: " << b << "\n"; // 0

	// �Ϲ����� ���ø� ��� ���� �޸� ���� ���� ���ø��� ����ϴ� �Լ��� callable unit���� �Ѱ��־�� �� ���, \
	�������ڿ� ���� ���ø� Ÿ�Ե��� ������־�� �Ѵ�.
	thread varg_thread(TaskVArg<int32, int32, int32, int32, string>, 1, 2, 3, 4, "hello");
	varg_thread.join();
	
	TaskVArg(1, 2, 3, 4, "hello"); 
	
	
}