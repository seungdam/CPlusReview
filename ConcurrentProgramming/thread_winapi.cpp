#include "pch.h"
#include <windows.h>

int32 global;
int32 thread_local tls = 0;

// Window���� Thread���� �Լ��� �Ѱ��� ��, ������ ���� ������ ����� �Ѵ�.
DWORD WINAPI WorkerThread(void* arg)
{
	
	for (int i = 0; i < 10'0000; ++i)
	{
		++tls;
	}
	return tls;
}

int main()
{
	// Window API������ ������ ���� �Լ��� �����Ѵ�. ::CreateThread()
	// 1. thread�� ���� �Ӽ� 
	// 2. �����庰 �Ҵ� ���� ũ�� 
	// 3. �Լ���
	// 4. �Լ� ����
	// 5. ������ ���� �ɼ�
	// 6. ������ ID
	

	//  ������ C/C++ �ڵ�� �ۼ��� ��� ���� ����� �����϶�� �Ѵ�.
	// CRT�Լ��� ����� ��, ������ �߱��ų �� �ֱ� �����̴�.
	
	auto thread_handle = ::CreateThread(0, 0, WorkerThread, 0, 0, 0);
	
	if (thread_handle != 0)
	{
		::CloseHandle(thread_handle);
	}
	::ExitThread(0);
}