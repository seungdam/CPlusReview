#include "pch.h"

// *** Dead Lock : ���� ����
// �Ͼ�� ���� �Ͽ� ���� ������ ����ϴ� ���¸� ���´´�.
//  - �߻� ����
// lock�� unlock�� pair�� ������ ���� ���
//  �� lock �� unlock ������ �ڵ忡�� ���ܰ� �߻��� ���
//  �� lock�� ����� �� unlock�� �������� ���� ���


//  RAII (Resource Acquisition Is Initialization)
// ���� ���� ��Ȳ�� �����ϱ� ����, �츮�� lock_guard, unique_lock, shared_lock
// �� ���� ���ؽ��� RAII�� �ǰ��� ó���ϴ� �Լ��� �ݵ�� ����ϴ� ���� ����.
// �ܼ��ϰ� ����ϴ� ��� lock_guard��..
// ��޽����� ����� ����ϴ� ��� unique_lock, shared_lock�� ����Ѵ�.

using namespace std;

mutex m;

class WorkerObject
{
	static int32 cnt;
public:
#pragma region lock_guard
	void operator()()
	{

		// exclusive-lock
		lock_guard lg(m);
		std::cout << "\033[32m[" << this_thread::get_id() << "]\033[0m" << "\033[31m Get Exclusive Locked.\033[0m\n";
		++cnt;
		std::cout << "	Current Conunt: " << "\033[33m" << cnt << "\033[0m\n";
	}
#pragma endregion
};



int32 WorkerObject::cnt = 0;

int main()
{
	thread t[100];

	for (auto& i : t)
	{
		i = thread(WorkerObject());
	}

	for (auto& i : t)
	{
		i.join();
	}
}