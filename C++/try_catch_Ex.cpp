#include "pch.h"


// ======= ���� ó�� ========
// �⺻������ try - catch���� ���
// Framework ���� Ȥ�� �׽�Ʈ�� �����ϴ� ���������� ����ϴ� ���� ����.
// ���ܹ��� �⺻������ ������ �ð��� ������Ű�� ������ ������ ���ѽ�Ű�� �����̴�.


// noexcept Ű����
// ���� �߻� ��, �ٷ� ���α׷� ���� 
// try - catch���� ó�� �ӵ��� ������ ������ ���ɸ鿡�� ����ϴ�.


// �־��� int �����Ͱ� ����Ű�� ���� 100�� �����ϴ� �Լ�
void SetValueToPointer(int32* b) 
{
	if (b == nullptr)
	{
		// ���ڰ� nullptr�̶�� �翬�� ���ܸ� �߻����Ѿ� �Ѵ�.
		throw std::runtime_error("STL ���� Class�� ���� ���� ó�� : input null value\n");
		//throw - 1; // � ���� �Ѱ��ִ� ���
		//throw "�ƹ��ų�"; // �� ģ���� ���� ����Ÿ�Կ� �����ε��� ���� �ƴϹǷ� ...���� �̵�
	}
	else
	{
		*b = 100;
	}
}


void CheckPointerValidation(int* b) noexcept// ���� �߻� ��, ���α׷� ����
{
	bool ok = noexcept(SetValueToPointer(b)); // ���� �߻� ���� Ȯ��
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
	// �߻��� ������ ���� �پ��� ���� ���̽��� ó���� �� �ִ�..
	catch (std::runtime_error& e) // STL���� �����ϴ� ���� Ŭ������ throw Ű���忡 ���� ȣ�⿡ ���� \
									��ü���� ������ ���� ������ ���� ������ �� �ִ�.
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