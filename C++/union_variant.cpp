#include "pch.h"
#include <variant>

using namespace std;

enum class TypeTag { CHAR, INT, DOUBLE};

// union since C & C++98
union Test
{
	char c;
	int i;
	double d;
	// ������ ȣ�� �Ұ���... --> Ŭ���� ���� ��ü�� ���� �� ����. ���� built-in type��
};

// [c]
// [  i  ]
// [   d       ]


// union�� ������ �����ϱ� ���� ������ TaggeUnion Wrapper Class

class TaggedUnion
{
	Test _udata;
	TypeTag _tag;
public:
	void set_char(char a) { _udata.c = a; _tag = TypeTag::CHAR; }
	void set_int(int a) { _udata.i = a; _tag = TypeTag::INT; }
	void set_dobule(double a) { _udata.d = a; _tag = TypeTag::DOUBLE; }
	
	bool is_char() { return _tag == TypeTag::CHAR; }
	bool is_int() { return _tag == TypeTag::INT; }
	bool is_double() { return _tag == TypeTag::DOUBLE; }

	char get_char() 
	{		if (is_char()) return _udata.c; 
			else throw std::invalid_argument("Not Char Data Uses.\n"); 
	}

	int get_int()
	{
		if (is_int()) return _udata.i;
		else throw std::invalid_argument("Not Int Data Uses.\n");
	}
	double get_double()
	{
		if (is_double()) return _udata.c;
		else throw std::invalid_argument("Not Double Data Uses.\n");
	}
};

// C++17 ���� ������ std::variant
// type-safe 
// �ڵ����� ����,�Ҹ��� ȣ�� ok
// ������ ���
// ������ ���� ���� with visitor pattern

class Base
{
	int id {0};
public:
	Base() = default;
	~Base() = default;

	virtual void func() {
		cout << "base.\n";
	}
};

class Derived : public Base
{
public:
	Derived() = default;
	~Derived() = default;

	virtual void func() override final 
	{
		cout << "Derived.\n";
	}
};

int main()
{
	Test t;
	t.c = 'c';
	std::cout << "char: " << t.c << "\n";
	t.i = 100;
	std::cout << "char: " << t.c << " int: " << t.i << "\n";
	t.d = 90000;
	std::cout << "char: " << t.c << "  int: " << t.i << "  double: " << t.d << "\n";
	

	variant<char, int, double> v;
	
	if(holds_alternative<char>(v)) auto c = std::get<char>(v); // == std::get<0>(v)
	if (holds_alternative<int>(v)) auto i = std::get<int>(v);
	if (holds_alternative<double>(v)) auto d = std::get<double>(v);


	// std::get�� ���� �� ��ҿ� ���� ���� �� std::hold_alternative�� ���� �ش� variant ��ü��
	// Ÿ���� ������ �� ����.
	Derived d;
	variant<std::reference_wrapper<Base>> b(std::ref(d));
	visit([](auto a) {  a.get().func(); }, b);
}