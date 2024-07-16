#include "pch.h"

using namespace std;

class scoped_thread
{
	thread t;
public:
	explicit scoped_thread(thread input_thread) : t(move(input_thread))
	{
		if (!t.joinable()) throw logic_error("Unable Thread\n");
	}
	~scoped_thread()
	{
		t.join();
	}
	scoped_thread(scoped_thread& sc) = delete; // ������� �Ұ�
	scoped_thread& operator=(scoped_thread& rhs) = delete; // ���� �Ұ�
};

int main()
{
	// *** scoped_thread \
	\
	 �׻� �������� ������ ����Ŭ�� �ֽ��ؾ��Ѵٴ� ���� �ſ� ������ ����. \
	�׷��ٸ� thread�� wrapping�ϴ� ��ü�� ������ join�� �˾Ƽ� ������ �� �ֵ��� �ϴ°� ��Ѱ�? \
	��� ���̵��� ���� �ؼ��� ���������� scoped_thread \
	scoped_thread�� thread�� encapsuled�� ����. like unique_lock, lock_guard

	scoped_thread st(thread([]() {cout << "Scoped Thread\n"; }));

}