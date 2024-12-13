#include "pch.h"

#ifdef __cplusplus
extern "C" { 
#include "func.h"
}
#else
#include "func.h"
#endif


// 1. db api
// 2. os api
// 3. third-party lib & framework
// 4. language with foreign function interface
//   ㄴ 다른 언어로 구현된 기능의 함수를 C언어를 위해서 구현해놓은 것.
//   ㄴ 왜? 파이썬은 비교적 c언어보다 느린 퍼포먼스를 보여주기 때문


// Code Compatibility 코드 호환성
// C언어 프로그램은 legal C++ 프로그램으로 호칭하는 것은 괜찮다. 왜? C는 C++언어의 subset이기 때문
// 하지만 그 역은 불가능하다. C에는 C++의 기능을 제공하지 않기 때문

// C99에서는 일부 호환되지 않은 특성이 존재하긴 한다. (designated initializer라는 것이 있는데 
// C++의 경우 C++20부터 등장한다.)


// 언제 보통 사용되는가? Binary Comatibility
// C++를 통해 제작한 라이브러리를 C언어 기반 바이너리 파일에서 활용한다면
// 1. 네임스페이스
// 2. 클래스
// 등의 기능의 추론이 불가능하다.
// 그렇기 때문에 항상 전역 네임스페이스와 빌트인 타입으로 이루어진 struct만을 활용해 제작해야한다.

// 그리고 extern "C" 를 붙여 어느 언어 기반에서 활용할 함수 인지 명시를 해줘야한다.
// 이는 컴파일러의 Name Mangling을 방지하기 위함이다.

//  보통 이렇게 C/C++간의 호환성을 제공하기 위한 interface는 두 언어에서 모두 활용할 수 있어야하며,
// 서로 다른 두 언어만의 버전을 모두 포함해야한다.

// 이때 C++은 문제가 되지않지만 C의 경우 C++ 버전을 포함했을 때 C언어 컴파일에 에러가 발생할 수 있으므로
// C++ 버전의 함수를 숨겨야한다. 이러한 작업을 Conditional Compilation이라고 일컫는다.

// #ifdef __cplusplus ...  ==> exclude from C Language Compiler

int main()
{
	std::vector<int> v{ 1,2,3,4,5 };
	print_arr(v.data(), v.size());
	std::map<int, int> m;
	m.insert({1,1});
	std::vector<MyPair> v2;
	for (auto [key,value] : m)
	{
		v2.push_back({ key,value });
	}
	print_map(v2.data(), v2.size());
}

// *** resource management
// c : malloc, free ==> no raii, no smart ptr, should make tidy-up function
// c++: new delete

// 해당 리소스와 관련된 관련 문서를 읽어보는 것이 중요하다.