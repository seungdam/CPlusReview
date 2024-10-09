#include "pch.h"

// *** weak_ptr
//  1. weak_ptr�� ����Ʈ �����Ͱ� �ƴϴ�.
//  2. shared_ptr�� �־� ������ ��Ī�� �����ϱ� ���� ������ �������̴�.
//  3. �׷��� ������ ���������� ���� �׼����� �� ������, ���۷��� ī���ÿ��� ������ ��ġ�� �ʴ´�.
//  4. dangling pointer ������ �����ϱ� ���� �������ε� �̿�ȴ�.

// *** Important
// weak_ptr�� ���� ������ ���� �����Ͱ��� ��ȯ ������ �ذ��ϱ� ���Ե� �ִ�.

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

	// weak_ptr --> shared_ptr�� conversion�� �����ϴ�. ��, shared_ptr�� valid�� ��쿡�� �ش��Ѵ�.
	// �� weak_ptr�� shared_ptr�� conversion �� ��, conditional�� Ȯ���ϸ� �� ����Ʈ �����Ͱ� ��ȿ���� �� �� �ִٴ� ��.
	// caching �� ������ �� �̸� Ȱ���� �� �ִ�.

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
	provider->set_customer(costmer); // customer ref-cnt = 2; ��ȯ ���� �߻�...

	// ������ ptr�� weak_ptr�� �����ϸ� ���� �ذ�
	
}