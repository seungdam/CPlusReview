#include<iostream>
#include<iomanip>

using namespace std;

//���(Output)
// ���α׷� --> ��Ʈ�� ���� <-- write
//		(std::cout)   (std::streambuf)
//
//�Է�(Input)
//	���α׷� <-- ��Ʈ�� ���� <--read
//		 (std::cin)        (std::streambuf)

int main()
{
	int id1 = 2018182019;
	int id2 = 10000;
	// stream maipulator - endl(new line + flush), flush
	// sticky manipulator - left,right, setw, setfill
	cout << setw(15)  << "OHSD ID: " << left << id1 << "\n";
	cout << setw(15) << right << "KIMSH ID: " << left << id2 << "\n";
	
	auto pi = 3.141'592'653'5l; // 6�ڸ����� �ۿ� ǥ��ȵ�.
	cout << fixed << pi << "\n"; // �Ϲ����� ǥ���.
	cout << scientific << pi << "\n"; // e+000��(mantissa) ǥ��
	auto e{ 1.062e-19 };
	cout << e << "\n";

	cout << setprecision(3) << "Set Pi as 3: " << pi << "\n";

}