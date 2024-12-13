#include "pch.h"


// constexpr function
// 1. fuction body에서 아무런 함수 인자, 지역/전역변수 값의 변경을 허용 x ==> pure한 상태
// 2. 함수 인자 및 리턴 값도 const-expression 값만
// 3. 자동으로 inline의 형태로 작성된다. 왜? 함수 호출이 생략되기 때문이다.
// 4. 즉 다중 정의가 가능하다는 것.
// 5. 보통 lib 제작 과정에서 많이 활용함.

// 6. compile time에 computing하기 때문에 runtime overhead가 x


constexpr double km_to_mile(double mile) { return mile * 1.602; }

const double a = km_to_mile(40); // ok 컴파일 타임 결정

int d = 100;
double b = km_to_mile(d); // ok 런타임 결정

constexpr double f = 50;
constexpr double c = km_to_mile(f); // ok 컴파일 타임 결정

// 메타 프로그래밍(Meta Programming)


// *** const VS constexpr
// const는 상수로써 취급한다는 것이기 때문에, 컴파일이 아닌 런타임 중에 이를 판단할 수 있음.
// constexpr는 리터럴로 취급하기 때문에 컴파일 타임에서 판단할 수 있는 값임.

// *** inline VS constexpr  
//  constexpr ==> inline + 최적화 (이를 위해 inline보다 더많은 제약사항을 가짐)


// constexpr memeber
// static 변수 관련해서 컴파일 타임에 결정할 때 활용하는 것이 좋음.


class MyClass
{
private:
	int32 x{0};
	int32 y{0};

public:
	constexpr MyClass(const int& a) : x(a) 
	{
		// 좋지않은 사용 케이스라고 볼 수 있음.
	}
	constexpr MyClass(const int& a, const int& b) : x(a) , y(b)
	{
	}
	
	constexpr ~MyClass()
	{

	}
};

// constexpr 함수
constexpr int32 multiply(const int32& x, const int32& y) { return x * y; }

int main() 
{

	int32 x = 100;
	const int32 cx = 100;
	constexpr int32 cex = 100;

							//constexpr 키워드 없이도 해당 생성자를 호출할 수 있다.
	MyClass m(1);           // OK 이때는 기본 생성자로처럼 동작된다. \
							      다만 y를 초기화하지 않았음으로 좋은 관례는 아니다.
	
//  constexpr MyClass m(1)  // NO y가 초기화되지 않았기 때문에 컴파일 시간에 결정할 수 X
	

	
	MyClass m2(1, x);		// OK (런타임에 결정) 변수를 사용해 초기화하는 것이 가능하다.
	const MyClass m3(1, x); // OK (런타임에 결정) 
	
	

	// constexpr MyClass m4(1, x);  NO 반면 constexpr 키워드를 붙인 클래스는 변수를 \
									   초기화에 사용할 수 없다. 

	constexpr MyClass m4(1, cx);     // OK (런타임에 결정) 하지만 해당 변수가 const 타입 변수라면 가능
	constexpr MyClass m5(1, 10);     // OK (컴파일 타임에 결정)
	constexpr MyClass m6(cex, cex);  // OK (컴파일 타임에 결정)

	// constexpr 함수
	int32 mx = 10;
	int32 my = 100;
	const int32 cmx = 10;
	const int32 cmy = 100;

	int32 retval = multiply(mx, my); // OK (런타임에 결정)
	int32 retval2 = multiply(cmx, my); // OK (런타임에 결정)
	const int32 retval3 = multiply(mx, my); // OK (런타임에 결정)
	const int32 retval4 = multiply(mx, cmy); // OK (런타임에 결정)

	constexpr int32 retval5 = multiply(1, 10); // OK   (컴파일 타임에 결정)
//  constexpr int32 retval5 = multiply(mx, my);   NO
	constexpr int32 retval6 = multiply(cmx, cmy); // OK  (컴타임 타임에 결정)
	constexpr int32 retval7 = multiply(cex, cex); // OK  (컴파일 타임에 결정)
}


// =========== 게임 프레임워크 제작 시에는 어떻게 활용될 수 있는가?

// 게임이 수행되는 과정에서 정적인 값(Config, 리소스 식별자, 유틸리티)에 관해서는 constexpr 키워드를 적극적으로 활용하는게 좋다.
// 반면, 지속적으로 상태가 변화하는 Player, Monster 클래스에는 활용하기 적절하지 않다.
// 게임 내에서 사용할 수식 연산에서 활용하면 큰 도움이 될 것이다.