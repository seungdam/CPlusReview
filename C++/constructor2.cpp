#include <iostream>

using namespace std;


class Object
{
	int data{ 0 };
public:
	// Class Design Pattern DRY: Dont repeat Yourself
	// �⺻ �����ڿ� ���� ���� �����ε��� ����Ǿ��ٸ�, �ߺ��� �ڵ尡 ���ٴ� ��. ==> �����丵�� �ʿ�
	explicit Object() { cout << "Default Constructor\n"; }
	Object(const int& arg) : data(arg) { cout << "Parameter Constructor\n"; }
	Object(const Object& rhs) { cout << "Copy Constructor\n"; }
	
	// Ref Ÿ������ ��ȯ���Ѿ� = �� ���� ��ø ������ ó���� �����ϴ�.
	Object& operator=(const Object& rhs)
	{
		data = rhs.data;
		cout << "Copy Assign Operation\n";
		return *this;
	}

	~Object() { }

	// Conversion(����ȯ) Operator
	// �̷� ��� �ش� ����ȯ ���꿡 ���� �����Ϸ��� �Ͻ������� Ȱ���� �� �ִ�.
	operator int() const { cout << "Object[" << data << "] " << "Conversion to Int.\n";  return data; }
	 
	// �̷� ������ �����ϱ� ���ؼ� explicit Ű���带 Ȱ���ؾ��Ѵ�.
	// explicit Ű���� Ȱ���, cast �Լ��� ����� ������� ��ȯ�� �ƴ϶�� ����ȯ�� ������� �ʴ´�.
	explicit operator bool() const { return data; }
};

// Synthesize Function (�ڵ� ���� ������)
// �����Ϸ��� ���� �ڵ����� �����Ǵ� ��� �Լ���
// 1. �⺻, ����, ���� ����, �Ҹ��� �⺻������ �����ȴ�.
// 2. ���� ���縦 �����ϱ� ������ ���� ���縦 ������ �� ���� �����ؾ��Ѵ�.
// 3. ���Ƿ� ������ �����ڰ� ������ ��� �����Ϸ��� �ڵ� ������ �������� �ʴ´�.
/* 4. default / delete Ű���带 ���� �����Ϸ��� �̸� �ڵ� �����ϵ��� ������ �� �ִ�.
         *** default 
		      �翬�ϰ� �ۼ��ؾ� �� ������ �ڵ� �ۼ��� ������ �� �ִ�.(�����Ϸ��� �������ֱ� ����.)
			 �̴� �ڵ��� �������� ����Ű�� �Ϳ��� ������ �ȴ�.
			 �׸��� ����� ��ȭ�� �ִ��� �����Ϸ��� �ڵ����� �������ش�.

			*** delete
			 ����Ǿ� �ִ� �Լ����� ������ ȣ���� �� ����.
			 Conversion�̳� Overloading�� ������ �� Ȱ���Ѵ�. ==> �ֿ� Ȱ������� ���� ���� �� ���� �Ҵ��� �����ϴ� ��
			 default�� �޸� ��뿡 ������ ����.

	�����ؾ��� ������ 
	�ش� Ű���带 ����ϴ��� �����Ϸ��� �Լ��� synthesize �� �� ���� ��� delete ó���Ǳ� ������
	�� ����ؾ��Ѵ�.
 */    

class Test
{
private:
	// (1)���� ���
	// explicit Test(const Test& rhs) { cout << "Test Copy\n"; } // ���縦 �����ϰ��� �� �� private�� �ش� �����ڸ� �����ϸ� �ȴ�.
public:
	explicit Test() = default; // Synthesize Default Constructor
	
	// (1-2)Modern C++ ���
	explicit Test(const Test& rhs) = delete;
};

// Copy Elison 
// ���� ������ ���̱� ���� �����Ϸ��� ������ ����ȭ �ϴ� ��.

template<typename Ty>
Ty CopyElisonTempObj()
{
	return Ty();
}

// �̸��� �ο��� ��ü�� Copy Elison�� ������� ���� �� �ִ�.

template<typename Ty>
Ty CopyElisonNamedObj()
{
	Ty namedObj;
	return namedObj;
}


int main()
{
	Object obj;
	
	Object obj1{ 1 };
	Object obj2{ obj1 };

	cout << "\n\n===Copy Elison ===\n";
	Object obj3 = CopyElisonNamedObj<Object>();
	Object obj4 = CopyElisonTempObj<Object>();
	cout << "\n\n===Conversion Operator===\n";


	// obj1�� ���� Implicit Conversion �߻�. ==> �Ű����� ������ ȣ��
	// Implicit Conversion�� ������ ���� ������ �߻��ϱ� ������ �����ϴ� ���� ����.
	// Implicit Conversion�� ��ǥ���� ���÷δ� stream ��ü���� ����.
	// fstream f("���ϸ�");�� ���� �츮�� if(f)�� ���� stream ���¸� Ȯ���� �� ����. 
	int a = obj1 + 100;
	cout << "obj1 + 100 ==> a: " << a << "\n";

	Object obj5(obj1 + 10);
	cout << "Casting obj5 as int: " << static_cast<int>(obj5) << "\n";
	if (obj5) // if, for, while, ���׿����� or �� ������ ���� �Ϻ� statement������ explicit Ű����� ���þ��� �׻� �Ϲ��� ����ȯ�� �����ȴ�.
	{
		cout << "obj5's data is available!!\n";
	}
	
}