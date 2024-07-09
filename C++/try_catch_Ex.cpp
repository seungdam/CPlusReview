#include "pch.h"


// ======= 예외 처리 ========
// 기본적으로 try - catch문을 사용
// Framework 제작 혹은 테스트를 수행하는 목적에서만 사용하는 것이 좋다.
// 예외문은 기본적으로 컴파일 시간을 증가시키기 떄문에 성능을 제한시키기 때문이다.


// noexcept 키워드
// 예외 발생 시, 바로 프로그램 종료 
// try - catch보다 처리 속도가 빠르기 때문에 성능면에서 우월하다.


// 주어진 int 포인터가 가르키는 값에 100을 대입하는 함수
void SetValueToPointer(int32* b) 
{
	if (b == nullptr)
	{
		// 인자가 nullptr이라면 당연히 예외를 발생시켜야 한다.
		throw std::runtime_error("STL 예외 Class를 통한 예외 처리 : input null value\n");
		//throw - 1; // 어떤 값을 넘겨주는 방법
		//throw "아무거나"; // 이 친구는 따로 에러타입에 오버로딩한 값이 아니므로 ...으로 이동
	}
	else
	{
		*b = 100;
	}
}


void CheckPointerValidation(int* b) noexcept// 예외 발생 시, 프로그램 종료
{
	bool ok = noexcept(SetValueToPointer(b)); // 예외 발생 여부 확인
	std::cout << std::boolalpha << "Fun() noexcept? " << ok << "\n";
	SetValueToPointer(b);
}


int main()
{
	int32* b = nullptr;
	try
	{
		CheckPointerValidation(b);
	}
	// 발생한 에러에 관해 다양한 에러 케이스를 처리할 수 있다..
	catch (std::runtime_error& e) // STL에서 제공하는 예외 클래스로 throw 키워드에 의해 호출에 관해 \
									구체적인 오류에 관한 내용을 직접 정의할 수 있다.
	{
		std::cerr << e.what();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
	}
	catch (int32 e)
	{
		std::cerr << e << "\n";
	}
	catch(...)
	{
		std::cerr << "Excpetion Occured.\n";
	}
}