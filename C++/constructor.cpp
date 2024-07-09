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


	static int32 _sm ;	// ���� ��� ���� --> �Ϲ����� ��� �Լ����� ������ �� X
							// Ŭ���� ���� �������� ������ �ִ� �⺻ ���̱� ����.
	static const int32 _csm = 0;
public:
	
	// SampleClass() = default; 
	// default �����ڷ� �����ϱ�. ��? �����ڸ� �ϳ��� ������ ����,\
	   �����Ϸ��� ����Ʈ �����ڸ� ���������� X
	SampleClass() : _x(0), _y(0), _cx(2), _cy(1)
	{ 
		_name.assign("Default");
		std::cout << "�⺻ ������ ["<< _name<<"]\n";
	}

	// ��� �ʱ�ȭ ����Ʈ�� ����� Ŭ���� �ʱ�ȭ
	SampleClass(int32 x, int32 y, const char* name) : _x(x), _y(y), _cx(2), _cy(1)
	{ 
		_name.assign(name);
		std::cout << "�Ű� ���� ������ [" << _name << "] " << ++_sm << "\n";
		
	}
	
	// ��� �ʱ�ȭ ����Ʈ���� Class�����ڸ� ȣ���ϴ� ���
	// �̷��� �����ڸ� ���� �����ڶ�� �Ѵ�.
	// �׸��� ���� ������ �ȿ��� ȣ���ϴ� �����ڴ� ��� �����ڶ�� �Ѵ�.
	// �ش� �������� ����, �̵��� �߻��ϴ� ���� �ƴ϶�, ���� �������� ������ ���� �ʱ�ȭ �� ��,
	// ���� �����ڴ� �ٸ� ������ ��� �ʱ�ȭ ����Ʈ���� �ʱ�ȭ �� �� ����.

	SampleClass(int32 _x) :  SampleClass(_x, 100, "none")
	{

		// �ʱ�ȭ ���� -> SampleClass(only_x, 100) ������ ȣ�� -> �ش� ���� �������� �������� �̵�.
		// ��, ���� �̵��� ����Ǵ°� �ƴ϶� �ٷ� �������� �̵��Ѵٴ� ����
		
		std::cout << "���� ������";
		_x = 1000;
		
	}

	~SampleClass() 
	{ 
		std::cout << "�Ҹ��� [" << _name << "]\n";
	}

	// ���� �Լ�
	friend std::ostream& operator<<(std::ostream& os, const SampleClass& a)
	{
		os << a._x << " " << a._y << " " << a._cx << " " << a._cy << "\n";
		return os;
	}

	SampleClass operator+(const SampleClass& rhs)
	{
		// rhs�� _x, _y ��� private ���� ����������, �ش� ������ ������ Ŭ������ ���� ������ �ǹǷ�,
		// ���������� private ������� ������ �� �ִ�.(Friend);
		SampleClass result(_x + rhs._x, _y + rhs._y, "result");
		return result;
	}

	static void Init()
	{
		_sm = 0;
	}
};


// _sm�� �⺻������ private ���� ����������, �ʱ�ȭ�� ��� ���������� �̸� ������ �� �ִ�.
int32 SampleClass::_sm = 0;

int main()
{
	
	SampleClass a(10,10,"a");
	SampleClass b(10,10,"b");
	a + b;

}