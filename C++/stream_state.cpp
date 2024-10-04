#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


// Stream State: stream ��ü�� ���������� �۾��� ����� ���� ��ȯ�� ���ش�.
// ::good(): ���� �� , return true
// ::fail(): ���� ��(Wrong formated data r/w), return true 
// ::bad(): ���� �Ұ����� error �߻� ��(Serious error such as disk), return true

int main()
{
	fstream ffile{ "output.txt", ios::in};
	if (ffile.good()) std::cout << "File Successfully Open!\n";
	int val{ 0 };

	while (ffile >> val)
	{
		cout << val << " ";
	}
	if (ffile.fail()) cout << "\nWrong Formatted Value\n";
	//while (!ffile.eof()) // it is not proper code
	//{
	//	file�� �� ���ο� ���� ���� ��, �̸� �����Ѵ�.
	//	�� x�� ���� ������ 9�� �����ϴ� ��
	//	ffile >> val;  ==> ������ new line�� ���� ó�� x
	//	cout << val << " ";
	//}
	ffile.close();
	
	auto x = 0;
	auto bSuccess{ false };
	cin >> x;
	while (!bSuccess)
	{
		if (cin.good()) bSuccess = true;
		else
		{
			// cin�� flush�� �������� �ʴ´�. �׷��� ������
			// ignore()�� ����� buffer�� ����� ������ stream���� ������ �� �ִ�.
			cin.clear(); // buffer�� �ʱ�ȭ�ϴ� ���� �ƴ�. cin�� ���¸� �ٽ� valid�ϰ� �ʱ�ȭ
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> x;
		}
	}
}