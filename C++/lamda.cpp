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
		// this 캡처도 가능하다.
		// 이렇게 하면 해당 객체의 멤버를 reference 형태로 멤버에 접근할 수 있다.
		// *this -> value 타입으로 캡처

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
	// value값을 반환하는 단일 문장만 반환 타입을 유추할 수 있었다.
	// 그 이외에 복잡한 람다함수는(다중 분기) 반환타입이 void로 추론되기 때문에 ->반환타입 을 통해 타입을 직접 명시해줘야 했다.

	auto iter = std::find_if(begin(nums), end(nums), [](auto elm)->bool { return elm > 5; });
	// c++14 
	// auto 타입을 인자로 삼는 Generic Lamda 표현이 가능. 
	// 직접 멤버 데이터 초기화하는 기능도 지원. ==> [n = 3]() {...}. 어떻게? move 시멘틱을 사용하기 때문
	// 다중 분기에 관해 모든 경로에 동일한 타입의 반환값을 제시해야한다.
	auto iter2 = std::find_if(begin(nums2), end(nums2), [](auto elm) { return elm > 5; });
	// c++17 모든 분기에 관해 반환할 필요도 없다.
	
	string s{ "hello" };
	string s2{ "Hello" };
	
	cout << boolalpha << std::equal(cbegin(s),cend(s), cbegin(s2),cend(s2), 
		[](auto& lhs, auto& rhs) 
		{
			return toupper(lhs) == toupper(rhs);
		}
	);


	// *** lamda capture
	// lamda 함수는 기본적으로 외부에서 온 지역변수를 활용할 수 없다.
	// only non-local variable(static, global 변수)만 활용할 수 있다.
	
	static int svar{100};
	int a{100};
	auto lm = []() 
	{ 
		cout << global << "\n";
		cout << svar;
		// cout << a; 불가능
	};

	// 이를 위해 제공하는 기능이 capture 기능이다.
	// capture를 사용할 경우, 컴파일러는 functor를 구현할 때,
	// 이를 위한 데이터 멤버를 추가하여 컴파일을 수행한다. (const하기 때문에 수정할 수 없다)
	// 해당 데이터 멤버는 생성자에 들어오는 캡처값에 의해 초기화되며, 그 값을 복사한다.

	// mutable을 통해 값을 내부적으로 변화시킬 수 있지만 원본값엔 영향을 주지않는다.
	auto captureLm = [n = a]() { cout << n << "\n"; };
	auto captureLm2 = [n = 3]() { cout << n << "\n"; };
	auto captureLm3 = [a]() { cout << a << "\n"; }; // ++a 불가능
	auto captureLm4 = [a]() mutable {cout << ++a << "\n"; };
	captureLm();


	auto capByRef = [&]() {/*모든 외부 지역 변수를 참조*/};
	auto capByVal = [=]() {/*모든 외부 지역 변수를 복사*/};

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

