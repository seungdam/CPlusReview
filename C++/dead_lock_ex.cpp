#include "pch.h"




// 서버에서 크래시가 발생하는 경우
// 1. Dead Lock 데드락
// 2. Nullptr Crash 



// 아래 예시는 Dead Lock을 완벽하게 해결한 케이스는 아니므로 주의해야함.
class User
{
public:
	User() {}
	~User() {}
};

class UserManager
{
	std::mutex user_lock;
private:
	UserManager() {}
	~UserManager() {}

public:
	static UserManager* Instance()
	{
		static UserManager* instance = nullptr;
		if (instance == nullptr)
		{
			instance = new UserManager();
		}
		return instance;
	}

	static void ReleaseInstance()
	{
		UserManager* instance = Instance();
		if (instance != nullptr)
		{
			delete instance;
		}
	}
public:
	User* GetUser()
	{
		std::lock_guard<std::mutex> lg(user_lock);
		return nullptr;
	}
	void ProcessSave();
};

class Account
{

public:
	Account() {};
	~Account() {};
};

class AccountManager
{
	//std::unordered_map<int32_t, Account> users;
	std::mutex account_lock;
private:
	AccountManager() {};
	~AccountManager() {};
public:

	// singleton pattern design
	static AccountManager* Instance()
	{
		static AccountManager* instance = nullptr;
		if (instance == nullptr)
		{
			instance = new AccountManager();
		}
		return instance;
	}
	static void ReleaseInstance()
	{
		AccountManager* instance = Instance();
		if (instance != nullptr)
		{
			delete instance;
		}
	}
#pragma region Singleton Pattern2
	// sigleton pattern design by scott myatt
	/*static AccountManager& GetInstance()
	{
		static AccountManager instance;
		return instance;
	}*/
#pragma endregion

	Account* GetAccount() 
	{ 
		std::lock_guard<std::mutex> lg(account_lock); 
		return nullptr; 
	}
	void ProcessLogin()
	{

#pragma region Dead Lock Case
		/*std::lock_guard<std::mutex> lg(account_lock);
		UserManager::Instance()->GetUser();*/
#pragma endregion

#pragma region No Dead Lock Case
		UserManager::Instance()->GetUser();
		std::lock_guard<std::mutex> lg(account_lock);
#pragma endregion
	}
};


void AccountThread()
{
	for (int i = 0; i < 10000; ++i)
	{
		AccountManager::Instance()->ProcessLogin();
	}
}

void UserThread()
{
	for (int i = 0; i < 10000; ++i)
	{
		UserManager::Instance()->ProcessSave();
	}
}


int main()
{
	std::thread t1(AccountThread);
	std::thread t2(UserThread);

	t1.join();
	t2.join();

	std::cout << "Job Done";


	std::mutex m1;
	std::mutex m2;
	std::lock(m1, m2); // lock을 일관적인 순서를 보장해서 locking하기

	// std::adopt_lock : 해당 lock은 이미 잠긴 상태이므로 해제만 제대로 수행하라는 옵션
	std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
	std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
}

void UserManager::ProcessSave()
{
	std::lock_guard<std::mutex> lg(user_lock);
	AccountManager::Instance()->GetAccount();
}
