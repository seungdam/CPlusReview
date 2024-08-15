#include "pch.h"
#include <condition_variable>
#include <sstream>
#include <queue>
// 2024-07-31

// *** Condition_Varable ���� ����
// �̺�Ʈ �޽��� ������ ���� ������ ����ȭ ���
// �ּ� �� �� �̻��� �����尡 �ʿ��ϸ�, �ϳ��� ������(�޽��� ����)
// �� ���� �޽��� �߽���(�޽��� ����)�� �Ǿ���Ѵ�.


// 2024-08-13
// unique_lock�� �Բ� ����Ѵ�.
// Why? condition_variable::wait(lock, predicate())�� ���, predicate�� ���� Ȱ��Ǵµ� 
// predicate�� return ���� ���� �����ϴ� ��� ��ü�� ���� lock(), unlock()�� �ֱ������� ȣ���ϱ� �����̴�.
// lock_guard�� �߰��� �����ϴ� ��� ��ü�� ���� unlock�� �Ұ����ϹǷ� wait�� �Բ� ����� �� ����.

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid(1, 2);
uniform_int_distribution<int> rgb(1, 230);

using namespace std;

// Critical Data
queue<int32> shared_queue;

mutex m;
condition_variable cv;		
condition_variable_any cva; // BasicLockable�� ������ ��� ����� ���� ��ü���� Ȱ�밡��



// Condition Variable WorkFlow

// *** 1. Supurious Wake Up
//  ���� ���̵� �� ���� �۵��Ǵ� ���(������ ���� ������ ������ ��� Ȯ�� ����) 
//  � flag ���� predicate���� Ȱ���� ��, wait�� ȣ���ϱ� ������ �̹� ������ �����ϴ� ���, �߻��Ѵ�.					 
 
// *** 2. Lost Wake Up  
// �����尡 Wait ���¿� �����ϱ� ��, �̹� ������ ������ ���. 
// ������ ���� ������ ���̸� ����� �߻�

void Task(int32 color)
{
	auto flag = false;

	for (int32 iter = 0; iter < 5; ++iter)
	{
		if (flag)
		{
			printf("                                                            \r");
			PrintThreadMsg(color, "[Consumer]\033[0m \033[1;33mDo Tasking...\r");
			flag = false;
		}
		else
		{
			printf("                                                            \r");
			PrintThreadMsg(color, "[Consumer]\033[0m \033[1;33mDo Tasking....\r");
			flag = true;
		}

		this_thread::sleep_for(0.3s);
	}
	printf("\n");

	PrintThreadMsg(color, "[Consumer]\033[0m\033[1;33m Job Finishied\n\033[0m");
}

void Producer()
{
	
	auto tcolor = rgb(dre);
	auto elm = 0;
	while (true)
	{
		shared_queue.pop();
		lock_guard<mutex> lg(m);
		shared_queue.push(elm++);
		PrintThreadMsg(tcolor, "[Producer]\033[1;33m Queue Data Set: ", elm , "\033[0m\n");
		cv.notify_one();
		this_thread::sleep_for(0.2s);
		
		
	}
}

void Consumer()
{
	auto tcolor = rgb(dre);
	while (true)
	{
		std::unique_lock<std::mutex> ul(m);
		if (shared_queue.empty())
		{
			cv.wait(ul); 
		}
		
			PrintThreadMsg(tcolor, "[Consumer]\033[1;33m Wake Up ", "\033[0m\n");
			shared_queue.pop();
		
	}
}


int main()
{
	jthread t[5];

	t[0] = jthread(Consumer);
	t[1] = jthread(Consumer);
	t[2] = jthread(Consumer);
	t[3] = jthread(Consumer);
	t[4] = jthread(Producer);
}