#include "pch.h"




// �������� ũ���ð� �߻��ϴ� ���
// 1. Dead Lock �����
// 2. Nullptr Crash 



// �Ʒ� ���ô� Dead Lock�� �Ϻ��ϰ� �ذ��� ���̽��� �ƴϹǷ� �����ؾ���.
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
	std::lock(m1, m2); // lock�� �ϰ����� ������ �����ؼ� locking�ϱ�

	// std::adopt_lock : �ش� lock�� �̹� ��� �����̹Ƿ� ������ ����� �����϶�� �ɼ�
	std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
	std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
}

void UserManager::ProcessSave()
{
	std::lock_guard<std::mutex> lg(user_lock);
	AccountManager::Instance()->GetAccount();
}
