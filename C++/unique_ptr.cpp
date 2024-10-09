#include "pch.h"
#include <memory>

// Memory Leak
// Dangling Pointer
// 등 힙 영역에 동적으로 할당한 메모리를 관리하는 것에 있어서 사용자의 역량에 기댈 경우
// 발생할 수 있는 다양한 문제점을 개선하기 위해 등장한 스마트 포인터
// *** 동적 바인딩에도 활용 가능


//  Smart Pointer는 할당된 메모리를 캡슐화한 Wrapper Class

// 1. 오직 public M.F를 통한 접근만이 허용된다.
// 2. RAII 방식으로 구현되어 있다.
// 3. 얕은 복사와 관련된 이슈가 발생하지 않는다.
// 4. 포인터를 덮어쓰거나 무효화 시킬 수 없다.

// *** unique_ptr --> auto_ptr의 개선버전(auto_ptr 등장 당시 move semantic이 존재하지 않았음.)
// 복사, 할당이 불가능하지만 이동은 가능하다.
// 1. 대부분의 Heap Memory 할당 상황에서 유용하게 사용이 가능하다.
// 2. 굉장히 가벼운 클래스다. => 오버헤드가 적기 때문에, 일반적인 포인터를 사용하는 것과 다를게 없다.
// 3. 탬플릿 클래스로, 우리가 평소 활용하던 기본 포인터를 멤버로 가지고 있으며, 일부 연산 기능 또한 제공된다.
// 4. 탬플릿 인자로는 할당할 데이터의 타입이 들어간다. unique_ptr<int> uptr ==> int*
// 5. move-only class이다.

// *** shared_ptr --> shared_ptr간의 공유가 가능하다. Ref Counting이라는 방식을 채택해 동작한다.

// 두 요소 모두 동작하는데 시간이 많이 소요되기 때문에 필요한 상황에만 활용하는 것이 좋다.
struct Pos
{
	int x;
	int y;
};


void func(std::unique_ptr<Pos> uptr)
{
	std::cout << "Pass " << uptr << " to function.\n";
}

std::unique_ptr<Pos> make_unique_pos(int x, int y)
{
	Pos p{ x,y };
	auto upptr{ std::make_unique<Pos>(p) };
	return upptr; // 어차피 컴파일러가 move 최적화를 수행하므로 굳이 std::move를 붙일 필요는 없다.
}

int main()
{
	// C++11
	std::unique_ptr<int> uptr1{ new int{42} }; // new 문법과 함께 활용된다.
	std::unique_ptr<int[]> uptr2{ new int[6] }; // fixed-size-array 고정 길이 배열 또한 관리할 수 있다.

	// C++14
	// C++14부터는 make_pair와 같은 make_unique 라이브러리 함수가 제공. 
	// 당연히 perfect-forwarding을 제공한다.
	auto uptr3{ std::make_unique<int>(42) };
	auto uptr4{ std::make_unique<int[]>(6)};

	std::cout << "uptr1: " << uptr1 << " *uptr1: " << *uptr1 << "\n"; // 역참조 가능
	std::cout << "uptr2[0]: " << uptr2[0] << "\n"; // 배열의 인덱스를 통한 접근 가능
	// std::cout << *uptr2; ==> Error 배열 자체는 역참조 불가능하다.
	// ++ -- 와 같은 증감연산도 불가능
	// uptr1 = uptr2 와 같은 copy assign / copy constructor 호출도 불가능 ... 오직 move만 가능

	std::unique_ptr<int> uptr5{ std::move(uptr1)};
	uptr1 = nullptr; // nullptr을 대입하면 기존 할당된 메모리는 삭제된다.
	std::cout << "*uptr1: " << uptr1 << "\n";
	std::cout << "*uptr5: " << uptr5 << "\n";


	auto pos_uptr{ std::make_unique<Pos>(Pos{10,10}) };
	std::cout <<"pos_uptr: " << pos_uptr << " X: " << pos_uptr->x << " Y: " << pos_uptr->y << "\n";
	func(std::move(pos_uptr));

	std::cout << make_unique_pos(3, 6)->x;
} 