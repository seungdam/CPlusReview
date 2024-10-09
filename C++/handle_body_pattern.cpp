#include "pch.h"

// *** OPP에서는 클래스에 관한 인터페이스와 클래스의 내부 구현 내용을 분리할 필요가 있음.

// client <== [class interface] === [class implementation]

// 1. client(해당 클래스를 다루는 코드)는 오직 인터페이스를 통해 상호작용하며, 내부 구현사항을 알 필요가 없어야함.
// 2. class 내부에 구현된 내용들은 public m.f를 통해 제공되며,
//    그 이외에는 어떤 멤버든 클라이언트에게 공개되면 안된다.
// 3. 이로써 client는 class의 내부 코드가 수정되더라도 별다른 영향을 받지 않는다.
// 4. 오직 interface가 변경되었을 때만 영향을 받는다.


// 왜 필요한가?
// A. 우리가 보통 cpp에 구현 .h에 선언을 해놓는다. + 접근 지정자를 통해 member를 관리한다.
//   ㄴ 하지만 이것은 완전한 은닉 보장받지 않는다. 
//   ㄴ (prototype member or inline 함수 or 멤버의 타입/이름을 유추 할 수 있다.)

// A. 구현 부분이 조금이라도 바뀐다면 바뀐다면, 반드시 컴파일을 재수행해야한다..  
//  ==> 아무리 수정된 코드가 적다고 한들 시간이 오래걸리고 비효율적이다.

// client <==> handle(인터페이스) <==> body(구현부)

// class를 body와 handle로 구분 짓는다
// handle은 body 객체를 생성하고, client의 요청에 따라 공개된 m.f를 제공한다.
// 마치 client에게 body가 아닌 다른 객체인 것처럼 느끼게 한다.
// 하지만 실질적인 body기능은 모두 제공된다.

//1. handle.h <== handle 클래스 구현 (public m.f only)
//2. body.h <== 실제 body 객체를 구현 및 정의

// client에겐 handle.h만 include 
// 즉, body.h가 수정되도 client는 영향을 받지 않음. ==> client는 컴파일할 필요가 X

// 계층도
// 
//  body.h			   handle.h
//    |                 /    \
//  body.cpp    handle.cpp client.cpp
//    |               |       |
//    [        compiler        ] compile + link 
// 
// static linking: 각각의 단일 binary file들을 합처 하나의 binary file로 만드는 것.
           // body.exe + handle.exe = client.exe


// dynamic linking 
// body.h == body.cpp ==> body.lib
//                                \
//                                 \
// handle.h/.cpp == client.cpp ==> client.exe
// client.exe가 런타임 중 body.lib 라이브러리 파일의 내용을 활용한다.



// how to implement? 
// *** plmpl: pointer to implementation
// handle class가 body 클래스의 포인터를 가지는 것
// 이때 Handle Class는 RAII형태로 동작해야한다.

// 사용처
// 1. 대규모 프로젝트 혹은 라이브러리에서 활용
// 2. 컨테이너 클래스를 제작 혹은 활용할 때 유용하게 사용할 수 있다.

// 단점
// 1. Body 객체에 역참조를 수행하기 때문에 속도가 느리다.
// 2. Body 객체에 관한 추가적인 할당을 수행하기 때문에 메모리를 더 잡아먹는다.
// 3. 공유 라이브러리 형태의 프로젝트 구조는 프로그램 시작을 느리게한다.
// 4. 코드베이스의 복잡성을 야기시킨다.


class Body; // body 헤더를 추가하지 않고 전방선언으로 구현

class Handle
{
private:
    Body* _body; // unique_ptr로 대체해서 구현할 수 있다.
public:
    void func() {};
};

#include "HandleDate.h"

int main()
{
    HandleDate h(2024,10,9);
    h.PrintDate();

}