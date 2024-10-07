#include "pch.h"


using namespace std;


// fstream, iostream, thread ���� ��ü�� move only class�̴�.
// ���� raii ���·� �����Ǹ�, ���ҽ��� �Ҵ�޾� �����ϴ� ��찡 �ָ� �̷��.

class MoveOnlyClass
{
public:
	MoveOnlyClass() = default;

	MoveOnlyClass(const MoveOnlyClass& other) = delete;
	MoveOnlyClass& operator=(const MoveOnlyClass& rhs) = delete;
	
	MoveOnlyClass(MoveOnlyClass&& other) noexcept { cout << "\033[38;5;221mMove Con\n\033[0m"; }
	MoveOnlyClass& operator=(MoveOnlyClass&& other) noexcept { cout << "\033[38;5;221mMove Assign\n\033[0m"; return *this; }
};

int main()
{
	MoveOnlyClass moc;
	MoveOnlyClass moc2{ std::move(moc) };

	MoveOnlyClass moc3;
	moc3 = std::move(moc2);

    // �̷��� ��ü���� ���ٽ��� ���ڷ� �Ѱ��� �� �����ؾ��Ѵ�.

	// [moc3]{}(); copy capture not ok...

	[&moc3] { cout << "\033[1;31mLamda capture by ref. Don't tranfer ownership\n\033[0m"; }();
	[lmoc = std::move(moc3)] { cout << "\033[1;31mSince c++14 provide lamda capture by move semantic. Tranfer ownership\n\033[0m"; }();

	cout << "\n\n";
	vector<string> s(5);
	[&s] { cout << "\033[1;31mLamda capture by ref.\n"; }();
	[ls = std::move(s)] { cout << "\033[1;31mLamda capture by move semantic. \033[0mls size: " << ls.size() << "\n"; }();
	cout << "After Move.. s size: " << s.size();
} 