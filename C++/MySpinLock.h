#pragma once
class MySpinLock
{
// spinLock�� �ռ� lock�� �̹� �ɸ� ���¿��� � ������� �ൿ�ϴ� �Ϳ� ���� ������� �� \
�ش� lock�� �ٽ� �����ϱ� ������ ����ؼ� ������ �����ϴ� lock�̴�. \
��, busy - waiting (�ٻ� ���) ���¸� �����ϴ� lock�̶�� ���� �ȴ�. \
���� ū ������ context-switching�� ���� �����ϹǷ�, �����ս��� ����. \
����� �������� ��� PCB�� �ƴ� TCB��� ���� �ڽ��� ���ݱ��� �۾��� ������ ����Ѵ� \
������ �������δ�, ���� ��ü���� ������ ����Ǵ� ��� cpu �������� �������ٴ� ���� \
�Ϻ� ��Ȳ�� ���� ó�� �ӵ��� �����ٴ� ������ �ִ�.

public:
	// Lock�� ���õ� Ŭ���� ��ü���� lock, unlock�� default �޼ҵ� ������ �����Ѵ�.
	void lock()
	{
#pragma region ���������� ���� ó�� CASE -> ����� �۵� X
		while (_locked)
		{
		}
		_locked = true;
#pragma endregion

		bool expected = false;
		bool desired = true;
		// Atomic ������ CAS ������ ���� 
		// lock�� ���� -> lock�� �����ϴ� ������ ���������� ó������.
		while (!_locked.compare_exchange_strong(expected, desired))
		{
			expected = false;
		}
	}

	void unlock()
	{
		_locked.store(false);
	}

// c++�� volatile Ű����� �ش� Ű���尡 ���� ��ü�� ����\
�����Ϸ��� ���� ����ȭ�� �����ϱ� ���� ���Ǵ� Ű�����̴�.
// C#, java ����� �ٸ� ����� �߰������� �����ϹǷ�, �̿� ���ؼ��� ã�ƺ� �ʿ䰡 �ִ�.
// volatile bool _locked;

private:
	std::atomic<bool> _locked;

};

