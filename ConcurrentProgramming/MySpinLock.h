#pragma once
class MySpinLock
{
// spinLock은 앞서 lock이 이미 걸린 상태에서 어떤 방식으로 행동하는 것에 관해 얘기했을 때 \
해당 lock을 다시 점유하기 전까지 계속해서 경합을 수행하는 lock이다. \
즉, busy - waiting (바쁜 대기) 상태를 유지하는 lock이라고 보면 된다. \
가장 큰 장점은 context-switching을 적게 수행하므로, 퍼포먼스가 높다. \
참고로 스레드의 경우 PCB가 아닌 TCB라는 곳에 자신이 지금까지 작업한 내용을 백업한다 \
하지만 단점으로는, 많은 객체간의 경합이 진행되는 경우 cpu 점유율이 높아진다는 점과 \
일부 상황에 따라 처리 속도가 느리다는 단점이 있다.

public:
	// Lock과 관련된 클래스 객체들은 lock, unlock을 default 메소드 명으로 설정한다.
	void lock()
	{
#pragma region 원자적이지 않은 처리 CASE -> 제대로 작동 X
		while (_locked)
		{
		}
		_locked = true;
#pragma endregion

		bool expected = false;
		bool desired = true;
		// Atomic 변수의 CAS 연산을 통해 
		// lock에 접근 -> lock을 점유하는 과정을 원자적으로 처리하자.
		while (!_locked.compare_exchange_strong(expected, desired))
		{
			expected = false;
		}
	}

	void unlock()
	{
		_locked.store(false);
	}

// c++의 volatile 키워드는 해당 키워드가 붙은 객체에 관해\
컴파일러에 의한 최적화를 방지하기 위해 사용되는 키워드이다.
// C#, java 등에서는 다른 기능을 추가적으로 수행하므로, 이에 관해서는 찾아볼 필요가 있다.
// volatile bool _locked;

private:
	std::atomic<bool> _locked;

};

