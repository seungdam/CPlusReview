#include "pch.h"

// <windows.h>�� CreateThread() �޼ҵ尡 ����������
// �̽ļ��� ���� ���� ���̺귯�� ��������� �������

void Task()
{
	std::cout << "Do Task\n";
}

void PrintTheadIdTask(uint32 num)
{
	std::cout << std::this_thread::get_id() << "|"
		<< num <<  "\n";
	
}

int main()
{
	int32 thread_cnt = std::thread::hardware_concurrency(); // CPU �ھ� ����
	std::cout << "Core Count:" << thread_cnt << "\n";

	std::thread t(Task); // thread ��ü�� �ʱ�ȭ ��� 1

	std::thread t2; // thread ��ü�� �ʱ�ȭ ��� 2
	// �̷��� ��ü ���� �����ϴ� ���, ������ ��ü�� ����������, ��������� �ʴ´�.
	t2 = std::thread(Task); 
	// �̷��� ���� �����带 �����ϰ� �̵� ���� ������ �����ؾ� ��μ� t2�� ����ȴ�.
	
	
}