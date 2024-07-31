#include "pch.h"
#include <condition_variable>
#include <sstream>

// 2024-07-31

// *** Condition_Varable ���� ����
// �̺�Ʈ �޽��� ������ ���� ������ ����ȭ ���
// �ּ� �� �� �̻��� �����尡 �ʿ��ϸ�, �ϳ��� ������(�޽��� ����)
// �� ���� �޽��� �߽���(�޽��� ����)�� �Ǿ���Ѵ�.


// ���������� unique_lock�� �Բ� ���ȴٴ� Ư¡�� �ִ�.



using namespace std;

// Critical Data
bool shared_data{ false };

mutex m;
condition_variable cv;		// unique_lock�� ����
condition_variable_any cva; // BasicLockable�� ������ ��� ����� ���� ��ü���� Ȱ�밡��


void Task()
{
	for (int32 i = 0; i < 3; ++i)
	{
		printf("\r\033[1;31mDo Tasking ...\033[0m\r");
		this_thread::sleep_for(0.2s);
	}
	printf("\n");
}

void Producer()
{
	{	
		lock_guard lg(m);
		printf(t_set t_color_r "LG Locked.\n" t_reset);
		printf("[\033[33m Semder \033[0m] : Data Setting...\n");
		this_thread::sleep_for(0.3s);
		shared_data = true;
		printf(t_set t_color_r "LG UnLocked.\n" t_reset);
	}
	printf("[\033[33m Semder \033[0m] : Data Ready.\n");
	cv.notify_all();

}

void Consumer()
{
	stringstream ss;
	ss << this_thread::get_id();
	printf("[\033[33mReceiver\033[0m] : Waiting Job.\n");
	std::unique_lock<std::mutex> ul(m); 
	printf(t_set t_color_g "[%s]" t_reset t_set t_color_r " UL Locked.\n" t_reset, ss.str().c_str());
	cv.wait(ul, [] { return shared_data; }); 

	/* Same as below code
	
	while ([&]{return shared_data;}())
	{
		cv.wait(ul);
	}
	*/


	// *** Supurious Wake Up�̶� ���� ���̵� �۵��Ǳ� �Ѵ�.(������ ���� ������ ������ ���) ==> �� �ڵ忡�� �Ⱦ��� ����� �߻���;
	// �ٸ� ������ ���� ������ ���̸� Lost Wake Up���� ���� ����� �߻�
	
	// predicate �Լ����� ������ true�� �� �� ���� ����Ѵ�.
	// predicate ���� ����ϴ� ��쵵 �ִµ� �� ��� lock�� �ٷ� �����Ѵ�.
	// ���� wait�� ����ϴ� ���, �ݵ�� ������ �ʿ��ϴ�.

	
	// predicate - false : unlock() �� ���
	// predicate - true :  lock ���� ���� �� �ڵ带 �̾� ����
		
	Task();
	printf("[\033[33mReceiver\033[0m] : Job Finished.\n");
	
	printf(t_set t_color_g "[%s]" t_reset t_set t_color_r " UL UnLocked.\n" t_reset, ss.str().c_str());
}


int main()
{
	thread t[3];

	t[0] = thread(Consumer);
	t[1] = thread(Consumer);
	t[2] = thread(Producer);
	

	for (auto& i : t)
	{
		i.join();
	}
}