#include "pch.h"

// *** Dead Lock : 교착 상태
// 일어나지 않을 일에 관해 무한정 대기하는 상태를 일컫는다.
//  - 발생 요인
// lock과 unlock의 pair를 맞추지 않은 경우
//  ㄴ lock 과 unlock 사이의 코드에서 예외가 발생한 경우
//  ㄴ lock을 사용한 후 unlock을 수행하지 않은 경우


//  RAII (Resource Acquisition Is Initialization)
// 위와 같은 상황을 방지하기 위해, 우리는 lock_guard, unique_lock, shared_lock
// 과 같이 뮤텍스를 RAII에 의거해 처리하는 함수를 반드시 사용하는 것이 좋다.
// 단순하게 사용하는 경우 lock_guard를..
// 고급스러운 기능을 사용하는 경우 unique_lock, shared_lock을 사용한다.

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