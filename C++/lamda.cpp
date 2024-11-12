#include "pch.h"
#include <functional>

using namespace std;

int global{ 999 };

class GameObject
{
	int hp {1000};
public:
	void GetDamage(int dmg) { hp -= dmg; }
	void ScheduledAction() 
	{
		// this ĸó�� �����ϴ�.
		// �̷��� �ϸ� �ش� ��ü�� ����� reference ���·� ����� ������ �� �ִ�.
		// *this -> value Ÿ������ ĸó

		vector<std::function<void()>> action;
		action.push_back(([this]() { GetDamage(10);}));
	}

};


// lamda partial expression
auto greeter(const string& salutation)
{
	return [salutation](const string& name) { return salutation + " " + name; };
}


int main()
{
	// c++11
	vector<int> nums{ 1,2,3,4,5,6 };
	vector<int> nums2{ 1,2,3,4,5,6,7 };
	// value���� ��ȯ�ϴ� ���� ���常 ��ȯ Ÿ���� ������ �� �־���.
	// �� �̿ܿ� ������ �����Լ���(���� �б�) ��ȯŸ���� void�� �߷еǱ� ������ ->��ȯŸ�� �� ���� Ÿ���� ���� �������� �ߴ�.

	auto iter = std::find_if(begin(nums), end(nums), [](auto elm)->bool { return elm > 5; });
	// c++14 
	// auto Ÿ���� ���ڷ� ��� Generic Lamda ǥ���� ����. 
	// ���� ��� ������ �ʱ�ȭ�ϴ� ��ɵ� ����. ==> [n = 3]() {...}. ���? move �ø�ƽ�� ����ϱ� ����
	// ���� �б⿡ ���� ��� ��ο� ������ Ÿ���� ��ȯ���� �����ؾ��Ѵ�.
	auto iter2 = std::find_if(begin(nums2), end(nums2), [](auto elm) { return elm > 5; });
	// c++17 ��� �б⿡ ���� ��ȯ�� �ʿ䵵 ����.
	
	string s{ "hello" };
	string s2{ "Hello" };
	
	cout << boolalpha << std::equal(cbegin(s),cend(s), cbegin(s2),cend(s2), 
		[](auto& lhs, auto& rhs) 
		{
			return toupper(lhs) == toupper(rhs);
		}
	);


	// *** lamda capture
	// lamda �Լ��� �⺻������ �ܺο��� �� ���������� Ȱ���� �� ����.
	// only non-local variable(static, global ����)�� Ȱ���� �� �ִ�.
	
	static int svar{100};
	int a{100};
	auto lm = []() 
	{ 
		cout << global << "\n";
		cout << svar;
		// cout << a; �Ұ���
	};

	// �̸� ���� �����ϴ� ����� capture ����̴�.
	// capture�� ����� ���, �����Ϸ��� functor�� ������ ��,
	// �̸� ���� ������ ����� �߰��Ͽ� �������� �����Ѵ�. (const�ϱ� ������ ������ �� ����)
	// �ش� ������ ����� �����ڿ� ������ ĸó���� ���� �ʱ�ȭ�Ǹ�, �� ���� �����Ѵ�.

	// mutable�� ���� ���� ���������� ��ȭ��ų �� ������ �������� ������ �����ʴ´�.
	auto captureLm = [n = a]() { cout << n << "\n"; };
	auto captureLm2 = [n = 3]() { cout << n << "\n"; };
	auto captureLm3 = [a]() { cout << a << "\n"; }; // ++a �Ұ���
	auto captureLm4 = [a]() mutable {cout << ++a << "\n"; };
	captureLm();


	auto capByRef = [&]() {/*��� �ܺ� ���� ������ ����*/};
	auto capByVal = [=]() {/*��� �ܺ� ���� ������ ����*/};

	int x{ 42 }, y{ 99 }, z{ 0 };

	auto lam = [=, &z]() mutable 
	{ 
		++x; 
		++y; 
		z = x + y; 
	};
	lam();
	lam();

	cout << x << y <<" " << z << "\n";

	auto greet = greeter("Good Morning");
	cout << greet("James");

	int y2 = 1;
	auto l = [y2 = y2 + 1](int x) { return x + y2; };
	cout << l(5);
	cout << y2 << endl;

	auto p = make_pair<int, int>(1, 1);
}

