#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Concurrency of Modern C++ By Rainer Grimn (���� + ���������� ����)

// Thread�� �����ϱ� ���� (C++11 ����)
// ���ü��� ����ؾ��� �ʿ䰡 ���� ==> �÷����� �����Ϸ��� ������ ����ȭ ������ �ذ�
// ��κ��� ���μ����� �ϳ��� ���� �帧�� ���� �����ߴ�. (�̱� ������)
// �� ��� Sequence Point��� ������ �����ߴµ�,
// Sequence Point��, ���μ����� ��� �� ������ ���´´�.
// �̶�, Sequence Point �������� ������ ����� ��ɾ��� ����� ���� Sequence Point���� �̸� 
// ����� �� �־�� �Ѵ�. 

// Sequence Point�� Strong Memory Model�̶�� �θ��⵵ �Ѵ�.

// ���� ǥ�� Thread ���̺귯���� ���� (C+11 ����)

// ��Ƽ������ ȯ�濡�� ���α׷����� �����ϴٺ���, �޸� ������ �ϰ��� �� ���� ���ɼ���
// ������ �ʿ䰡 ����. ==> �̿� ���� C++ ǥ�� �޸� ���� �����ߴ�.
// 
// C++�� �޸� �� (Well - Defined Memory Model)
// C++�� �޸� ���� JAVA�� ����޾� �𵨸� �Ǿ�����, ������ �ϰ���(Sequence Consistency), ������ ����, �޸� ������ Ư¡�� ������.

// ������ �ϰ����� �����Ѵٴ� ���� ������ �ǹ��Ѵ�.\
1. ���� �������� ��ɾ�� ���α׷����� ������ ������� ����ȴ�. \
2. ��� ������� ������ �۾� ������ ����. (���� ���� ������ �ٸ� �� ����.) (Global Order)


// �׸���  C++ Memory Model�� �ٷ�� �ٽ� ������ ������ ����. \
\
1. *** Atomic Operation				  �Ұ����� �������� ����. == ����� �ٸ� ��ҿ� ���� �߰��� ���ع��� �� ���� �۾�\
2. *** Partial Odering of Operations  �����ĵǾ �ȵǴ� �Ϸ��� �������� ����\
3. *** Visible Effects of Operations  Ÿ �����忡 ����, ���� ������(=����)�� �ݵ�� "���"�Ҽ� �־�� �Ѵ�.					


// ��Ƽ �������� �����ϱ� ���� ������ ������ ������ ����.
// Relaxed Semantic ==> Acquire-Release Semantic ==> Sequenctial Consistency ==> MultiThreading


// Strong Memory Model VS Weak Memory Model \
\
���⼭ ���ڴ� Strong Memory Model ==> Sequential Consistency�� \
			  Weak Memory Model ==> Relaxed Sementics ��� ���´´�.\

// Weak Memory Model�ν� ��������� �̷���� ���, �����尣�� �������� ��������,\
�ý��� ���忡�� ����ȭ �� �� �ִ� �������� �þ�� �ȴ�.


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
	// ������ ������� ��� ������ �帧�� ����. ������ 1�� ������2�� �帧�� �����ϰ�, �� ���� ����������.
	// �׷��� ������ �ð� ������ ������ 1���� �ռ� �Ͼ ��ǿ� ���� ������2�� ������ �귯�ö� �� ���ٴ� ��.
	// �̰��� ���� ����(Global Order)��. ������ ����� ������ �ٸ� �� ������, 
	// �� ��Ȳ���� res�� �� �� 0,0�� ���´ٸ� sequencial consistency�� �����Ѵٴ� ���� �ǹ���.
	t1.join();
	t2.join();
}