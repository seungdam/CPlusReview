#include "pch.h"

// *** weak_ptr
//  1. weak_ptr은 스마트 포인터가 아니다.
//  2. shared_ptr에 있어 안전한 별칭을 생성하기 위한 일종의 서포터이다.
//  3. 그렇기 때문에 직접적으로 값에 액세스할 수 없으며, 레퍼런스 카운팅에도 영향을 미치지 않는다.
//  4. dangling pointer 현상을 방지하기 위한 수단으로도 이용된다.

// *** Important
// weak_ptr의 개발 목적은 공유 포인터간의 순환 참조를 해결하기 위함도 있다.

struct Customer;


struct Provider
{
	using SharedCustomer = std::shared_ptr<Customer>;
	SharedCustomer sptr;
	void set_customer(const SharedCustomer& sc)
	{
		sptr = sc; // sptr ref-cnt = 1;
	}
	~Provider() { std::cout << "P Destrocutor\n"; }
};
struct Customer
{
	using SharedProvider = std::shared_ptr<Provider>;
	using WSharedProvider = std::weak_ptr<Provider>;
	WSharedProvider sptr;

	void set_customer(const SharedProvider& sc)
	{
		sptr = sc;
	}
	~Customer() { std::cout << "C Destrocutor\n"; }
};

int main()
{

	// bad case...
	int* ptr = new int{ 42 };
	int* cptr = ptr;
	// two different pointer var have same address.

	delete ptr; // then what's happen to cptr..? 

	std::cout << *cptr << "\n"; // it gonna be crash in worst case.

	auto sptr{ std::make_shared<int>(42) }; // ref-cnt : 1
	std::cout << "before create wptr: " <<  sptr.use_count() << "\n";
	std::weak_ptr<int> wptr =  sptr ; // ref-cnt still 1
	std::cout << "after create wptr: " << sptr.use_count() << "\n";
	sptr = nullptr; // ref-cnt : 0 ==> release...

	// weak_ptr --> shared_ptr로 conversion이 가능하다. 단, shared_ptr가 valid할 경우에만 해당한다.
	// 즉 weak_ptr를 shared_ptr로 conversion 한 후, conditional을 확인하면 이 스마트 포인터가 유효한지 알 수 있다는 것.
	// caching 을 수행할 때 이를 활용할 수 있다.

	std::shared_ptr<int> sptr2{ wptr.lock()};
	if (sptr) std::cout << "Valid.\n";
	else std::cout << "Invalid.\n";

	try
	{
		std::shared_ptr<int> sptr3{ wptr };
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}

	auto provider = std::make_shared<Provider>(); // provider ref cnt = 1;
	auto costmer = std::make_shared<Customer>(provider); // provider ref cnt = 2; customer ref-cnt = 1;
	provider->set_customer(costmer); // customer ref-cnt = 2; 순환 참조 발생...

	// 한쪽의 ptr을 weak_ptr로 세팅하면 문제 해결
	
}