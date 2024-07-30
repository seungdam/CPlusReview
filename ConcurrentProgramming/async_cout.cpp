#include "pch.h"
class TryWorker // Make Callable Unit Object Class
{
public:
	TryWorker(const int32& id) : tid(id)
	{
	}
	void operator()()  // () Operator overloading for std::thread
	{
		for(int32 iter = 0; iter <= 3; ++iter)
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << tid << "] Work Done\n";
	}
private:
	int32 tid;
};

int main()
{

	// *** cout�� ���ʿ� thread-safe �� ��. �ٸ� Race-Condition ��, ������·� ���ؼ�
	// ȭ�鿡 ���̴� �����۾� ��ü�� ���������� ����ȴٴ� ���̴�.
	// �׷��� ������ ���� ��Ʈ�� ��ü(cout,cin ...etc)�� ���� mutex�� ����ϴ� ���� �������� ���� �����̴�.

	std::thread worker[50];

	for (int32 iter = 0; iter < 50; ++iter)
	{
		worker[iter] =  std::thread(TryWorker(iter));
	}
	
	for (auto& i : worker)
	{
		i.join();
	}
}