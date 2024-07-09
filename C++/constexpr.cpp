#include "pch.h"




// ��Ÿ ���α׷���(Meta Programming)


// *** const VS constexpr
// const�� ����ν� ����Ѵٴ� ���̱� ������, �������� �ƴ� ��Ÿ�� �߿� �̸� �Ǵ��� �� ����.
// constexpr�� ���ͷ��� ����ϱ� ������ ������ Ÿ�ӿ��� �Ǵ��� �� �ִ� ����.

// *** inline VS constexpr  
//  constexpr ==> inline + ����ȭ (�̸� ���� inline���� ������ ��������� ����)

 
class MyClass
{
private:
	int32 x;
	int32 y;

public:
	constexpr MyClass(const int& a) : x(a) 
	{
		// �������� ��� ���̽���� �� �� ����.
	}
	constexpr MyClass(const int& a, const int& b) : x(a) , y(b)
	{
	}
	
	constexpr ~MyClass()
	{

	}
};

// constexpr �Լ�
constexpr int32 multiply(const int32& x,const int32& y)
{
	return x * y;
}

int main() 
{

	int32 x = 100;
	const int32 cx = 100;
	constexpr int32 cex = 100;

	//constexpr Ű���� ���̵� �ش� �����ڸ� ȣ���� �� �ִ�.
	MyClass m(1);           // OK �̶��� �⺻ �����ڷ�ó�� ���۵ȴ�. \
							      �ٸ� y�� �ʱ�ȭ���� �ʾ������� ���� ���ʴ� �ƴϴ�.
	
//  constexpr MyClass m(1)  // NO y�� �ʱ�ȭ���� �ʾұ� ������ ������ �ð��� ������ �� X
	

	
	MyClass m2(1, x);		// OK (��Ÿ�ӿ� ����) ������ ����� �ʱ�ȭ�ϴ� ���� �����ϴ�.
	const MyClass m3(1, x); // OK (��Ÿ�ӿ� ����) 
	
	

	// constexpr MyClass m4(1, x);  NO �ݸ� constexpr Ű���带 ���� Ŭ������ ������ \
									   �ʱ�ȭ�� ����� �� ����. 

	constexpr MyClass m4(1, cx);     // OK (��Ÿ�ӿ� ����) ������ �ش� ������ const Ÿ�� ������� ����
	constexpr MyClass m5(1, 10);     // OK (������ Ÿ�ӿ� ����)
	constexpr MyClass m6(cex, cex);  // OK (������ Ÿ�ӿ� ����)

	// constexpr �Լ�
	int32 mx = 10;
	int32 my = 100;
	const int32 cmx = 10;
	const int32 cmy = 100;

	int32 retval = multiply(mx, my); // OK (��Ÿ�ӿ� ����)
	int32 retval2 = multiply(cmx, my); // OK (��Ÿ�ӿ� ����)
	const int32 retval3 = multiply(mx, my); // OK (��Ÿ�ӿ� ����)
	const int32 retval4 = multiply(mx, cmy); // OK (��Ÿ�ӿ� ����)

	constexpr int32 retval5 = multiply(1, 10); // OK   (������ Ÿ�ӿ� ����)
//  constexpr int32 retval5 = multiply(mx, my);   NO
	constexpr int32 retval6 = multiply(cmx, cmy); // OK  (��Ÿ�� Ÿ�ӿ� ����)
	constexpr int32 retval7 = multiply(cex, cex); // OK  (������ Ÿ�ӿ� ����)
}


// =========== ���� �����ӿ�ũ ���� �ÿ��� ��� Ȱ��� �� �ִ°�?

// ������ ����Ǵ� �������� ������ ��(Config, ���ҽ� �ĺ���, ��ƿ��Ƽ)�� ���ؼ��� constexpr Ű���带 ���������� Ȱ���ϴ°� ����.
// �ݸ�, ���������� ���°� ��ȭ�ϴ� Player, Monster Ŭ�������� Ȱ���ϱ� �������� �ʴ�.
// ���� ������ ����� ���� ���꿡�� Ȱ���ϸ� ū ������ �� ���̴�.