#include "pch.h"
#include <sstream>

using namespace std;

void NonInterruptibleWorker()
{
	int32 count(0);
	std::stringstream ss;
	ss << std::this_thread::get_id();
	uint64_t tid = std::stoull(ss.str());

	while (10 > count)
	{
		
		printf(t_set t_bold t_g "[%lld]"
			t_set t_bold t_y " Still Working... %d\n" t_reset, tid, count);
		this_thread::sleep_for(0.5s);
		++count;
	}

	printf(t_set t_bold t_g "[%lld]"
		t_set t_bold t_c " Job Finished...\n" t_reset, tid);
}

void InterruptibleWorker(stop_token stoken)
{
	int32 count(0);
	std::stringstream ss;
	ss << std::this_thread::get_id();
	uint64_t tid = std::stoull(ss.str());

	while (10 > count )
	{
		
		if (stoken.stop_requested())
		{
			printf(t_set t_g "[%lld]"
				t_set t_bold t_r " Stop Requested\n",tid);
			return;
		}

		printf( t_set t_g "[%lld]"
				t_set t_bold t_y " Still Working... " t_reset
				t_set t_bold t_p  "& Stoken is possible: " t_reset "%s\n", 
				tid, 
				stoken.stop_possible() ? "True" : "False");
		this_thread::sleep_for(0.5s);
		++count;
	}

	printf(t_set t_bold t_g "[%lld]"
		t_set t_bold t_c " Job Finished... %d\n" t_reset, tid,count);
}

int main()
{
	jthread jthr([] 
			{ 
			printf(t_set t_y "Joining Thread" t_set t_c " (C++20)\n" t_reset); 
			this_thread::sleep_for(5s);
			});
	// *** C++20 ���� �����ϴ� joining thread
	// RAII ��� �� Ȯ��� �������̽��� �����ϴ� Ư¡�� ����.
	// �Ҹ��ڿ��� join()�� ȣ���Ѵ�.
	// join()�� ȣ������ �ʾƵ� program�� terminate ���� �ʴ´�.

	// jthread�� ��� ������ std::stop_resource��� ģ���� �����µ�, �̸� Ȱ����
	// ������ ������ ������ �� ����. Interrupt �߻� ����

	// 


	// �Ҹ��ڿ��� join�� ȣ���ϱ� ������ main ������ ���� ���ȿ��� True�� �����Ѵ�.
	printf( t_set t_y "jthr.joinable: " 
			t_set t_p "%s\n", (jthr.joinable() ? "(True)" : "(False)"));

	jthread it(InterruptibleWorker);
	// ���� ���� stop_token�� ��������� �������� �������� �ұ��ϰ�, �ڵ忡 ������ ����.
	// �� ������ jthread���� �Ѱ��� callable_unit���� stop_source::get_stop_token�� ���������� ȣ���� �Ѱ��ֱ� �����̴�.

	jthread nit(NonInterruptibleWorker);
	
	this_thread::sleep_for(1s);

	nit.request_stop(); // No Effect
	it.request_stop(); // Yes Effect

	// jthread::request_stop() ==> private member�� stop_resource�� request_stop ȣ��

}