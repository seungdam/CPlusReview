#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Concurrency of Modern C++ By Rainer Grimn (원서 + 번역본으로 공부)

// Thread가 등장하기 이전 (C++11 이전)
// 동시성을 고려해야할 필요가 없음 ==> 플랫폼과 컴파일러에 의존해 동기화 문제를 해결
// 대부분의 프로세스가 하나의 제어 흐름에 따라 동작했다. (싱글 스레드)
// 그 대신 Sequence Point라는 개념이 존재했는데,
// Sequence Point란, 프로세스의 어느 한 지점을 일컫는다.
// 이때, Sequence Point 기준으로 이전에 실행된 명령어의 결과에 관해 Sequence Point에선 이를 
// 목격할 수 있어야 한다. 

// Sequence Point를 Strong Memory Model이라고 부르기도 한다.

// 공식 표준 Thread 라이브러리의 등장 (C+11 이후)

// 멀티스레드 환경에서 프로그래밍을 진행하다보니, 메모리 접근의 일관성 및 예측 가능성을
// 보장할 필요가 생김. ==> 이에 따라 C++ 표준 메모리 모델이 등장했다.
// 
// C++의 메모리 모델 (Well - Defined Memory Model)
// C++의 메모리 모델은 JAVA를 영향받아 모델링 되었으며, 순차적 일관성(Sequence Consistency), 원자적 연산, 메모리 순서의 특징을 가진다.

// 순차적 일관성을 보장한다는 것을 다음을 의미한다.\
1. 단일 스레드의 명령어는 프로그램에서 지정한 순서대로 진행된다. \
2. 모든 스레드는 동일한 작업 순서를 본다. (실제 실행 순서는 다를 수 있음.) (Global Order)


// 그리고  C++ Memory Model이 다루는 핵심 내용은 다음과 같다. \
\
1. *** Atomic Operation				  불가분한 원자적인 연산. == 절대로 다른 요소에 의해 중간에 방해받을 수 없는 작업\
2. *** Partial Odering of Operations  재정렬되어선 안되는 일련의 순차적인 연산\
3. *** Visible Effects of Operations  타 스레드에 관해, 공유 데이터(=변수)는 반드시 "목격"할수 있어야 한다.					


// 멀티 스레딩을 이해하기 위한 지식의 순서는 다음과 같다.
// Relaxed Semantic ==> Acquire-Release Semantic ==> Sequenctial Consistency ==> MultiThreading


// Strong Memory Model VS Weak Memory Model \
\
여기서 저자는 Strong Memory Model ==> Sequential Consistency로 \
			  Weak Memory Model ==> Relaxed Sementics 라고 일컫는다.\

// Weak Memory Model로써 계약조건이 이루어진 경우, 스레드간의 직관성이 떨어지고,\
시스템 입장에서 최적화 할 수 있는 선택지가 늘어나게 된다.


// Strong Memory Model Example 
atomic<int> x,y;


void Func1()
{
	x.store(1, std::memory_order_seq_cst);
	auto res = y.load();
}

void Func2()
{
	y.store(1);
	auto res = x.load(std::memory_order_seq_cst);
}

int main()
{
	thread t1(Func1);
	thread t2(Func2);
	
	// *** No store Operation can overtake load operation. (Global Order)
	// 각각의 스레드는 모두 동일한 흐름을 본다. 스레드 1도 스레드2의 흐름을 이해하고, 그 역도 마찬가지다.
	// 그렇기 때문에 시간 순서상 스레드 1에서 앞서 일어난 사건에 관해 스레드2가 역으로 흘러올라갈 수 없다는 것.
	// 이것이 전역 순서(Global Order)다. 실제로 실행된 순서는 다를 수 있지만, 
	// 이 상황에서 res가 둘 다 0,0이 나온다면 sequencial consistency를 위반한다는 것을 의미함.
	t1.join();
	t2.join();
}