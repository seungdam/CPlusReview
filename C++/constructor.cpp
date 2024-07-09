#include "pch.h"

class SampleClass
{
	friend class ostream;
private:
	int32 _x;
	int32 _y;
	std::string _name;

	const int32 _cx;
	const int32 _cy;


	static int32 _sm ;	// 정적 멤버 변수 --> 일반적인 멤버 함수에서 접근할 수 X
							// 클래스 생성 이전부터 가지고 있는 기본 값이기 때문.
	static const int32 _csm = 0;
public:
	
	// SampleClass() = default; 
	// default 생성자로 정의하기. 왜? 생성자를 하나라도 선언한 순간,\
	   컴파일러가 디폴트 생성자를 정의해주지 X
	SampleClass() : _x(0), _y(0), _cx(2), _cy(1)
	{ 
		_name.assign("Default");
		std::cout << "기본 생성자 ["<< _name<<"]\n";
	}

	// 멤버 초기화 리스트를 사용한 클래스 초기화
	SampleClass(int32 x, int32 y, const char* name) : _x(x), _y(y), _cx(2), _cy(1)
	{ 
		_name.assign(name);
		std::cout << "매개 변수 생성자 [" << _name << "] " << ++_sm << "\n";
		
	}
	
	// 멤버 초기화 리스트에서 Class생성자를 호출하는 방법
	// 이러한 생성자를 위임 생성자라고 한다.
	// 그리고 위임 생성자 안에서 호출하는 생성자는 대상 생성자라고 한다.
	// 해당 과정에서 복사, 이동이 발생하는 것이 아니라, 위임 생성자의 내용을 먼저 초기화 한 후,
	// 위임 생성자는 다른 변수를 멤버 초기화 리스트에서 초기화 할 수 없다.

	SampleClass(int32 _x) :  SampleClass(_x, 100, "none")
	{

		// 초기화 순서 -> SampleClass(only_x, 100) 생성자 호출 -> 해당 위임 생성자의 본문으로 이동.
		// 즉, 복사 이동이 진행되는게 아니라 바로 본문으로 이동한다는 뜻임
		
		std::cout << "위임 생성자";
		_x = 1000;
		
	}

	~SampleClass() 
	{ 
		std::cout << "소멸자 [" << _name << "]\n";
	}

	// 전역 함수
	friend std::ostream& operator<<(std::ostream& os, const SampleClass& a)
	{
		os << a._x << " " << a._y << " " << a._cx << " " << a._cy << "\n";
		return os;
	}

	SampleClass operator+(const SampleClass& rhs)
	{
		// rhs의 _x, _y 모두 private 접근 지정자지만, 해당 연산은 동일한 클래스에 관해 진행이 되므로,
		// 예외적으로 private 멤버에도 접근할 수 있다.(Friend);
		SampleClass result(_x + rhs._x, _y + rhs._y, "result");
		return result;
	}

	static void Init()
	{
		_sm = 0;
	}
};


// _sm은 기본적으로 private 접근 지정자지만, 초기화의 경우 예외적으로 이를 접근할 수 있다.
int32 SampleClass::_sm = 0;

int main()
{
	
	SampleClass a(10,10,"a");
	SampleClass b(10,10,"b");
	a + b;

}