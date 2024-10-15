#include "pch.h"

// *** shared_ptr ==> 공유 객체를 가르키는 Pointer 
//					  + Ref Counting 및 기타작업을 수행하는 Control Block으로 이루어짐.


// 1. 객체의 주소를 생성자에 넘겨 초기화하기 가능.
// 2. make_shared()를 통해 초기화 하는 것도 가능.
// 3. unique_ptr 개체를 shared_ptr 개체로 변환 가능. 그역은 안됨.
// 4. pointer vs unique_ptr --> 후자 승
// 5. unique_ptr vs shared_ptr --> shared_ptr는 ref-counting 등 컨트롤 블록의 기능으로 인해 오버헤드가 더큼..
// 그렇기 때문에 어떤 개체를 공유해야하는 상황에서만 활용하는 것이 좋음. 그 외에는 unique_ptr이 압승.
// 6. shared_ptr의 복사,이동 연산자체는 atomic하지만 포인터 접근은 atomic 하지 않음. c++20부터는 atomic shared pointer를 제공.
int main()
{
	std::shared_ptr<int> sptr{ new int{42} }; // 객체의 주소를 넘기기
	auto sptr2{ std::make_shared<int>(42) }; // make_shared 사용하기
	std::cout << sptr.use_count() << "\n";
	auto csptr = sptr; // copy cons   ref-cnt 1
	std::cout << sptr.use_count() << "\n";
	sptr2 = sptr; // copy assign ref-cnt 2  sptr2 ref-cnt = 0;
	std::cout << sptr.use_count() << "\n";
	auto msptr = std::move(sptr);
	std::cout << "after move: " << csptr.use_count() << "\n";
	msptr = nullptr; // release
	std::cout << csptr.use_count() << "\n";

}