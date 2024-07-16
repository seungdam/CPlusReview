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
	scoped_thread(scoped_thread& sc) = delete; // 복사생성 불가
	scoped_thread& operator=(scoped_thread& rhs) = delete; // 대입 불가
};

int main()
{
	// *** scoped_thread \
	\
	 항상 스레드의 라이프 사이클을 주시해야한다는 것은 매우 귀찮은 행위. \
	그렇다면 thread를 wrapping하는 객체를 정의해 join을 알아서 수행할 수 있도록 하는건 어떠한가? \
	라는 아이디어에서 나온 앤서니 윌리엄스의 scoped_thread \
	scoped_thread는 thread를 encapsuled한 개념. like unique_lock, lock_guard

	scoped_thread st(thread([]() {cout << "Scoped Thread\n"; }));

}