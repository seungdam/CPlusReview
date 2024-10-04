#include<iostream>
#include<iomanip>

using namespace std;

//출력(Output)
// 프로그램 --> 스트림 버퍼 <-- write
//		(std::cout)   (std::streambuf)
//
//입력(Input)
//	프로그램 <-- 스트림 버퍼 <--read
//		 (std::cin)        (std::streambuf)

int main()
{
	int id1 = 2018182019;
	int id2 = 10000;
	// stream maipulator - endl(new line + flush), flush
	// sticky manipulator - left,right, setw, setfill
	cout << setw(15)  << "OHSD ID: " << left << id1 << "\n";
	cout << setw(15) << right << "KIMSH ID: " << left << id2 << "\n";
	
	auto pi = 3.141'592'653'5l; // 6자리까지 밖에 표기안됨.
	cout << fixed << pi << "\n"; // 일반적인 표기법.
	cout << scientific << pi << "\n"; // e+000식(mantissa) 표기
	auto e{ 1.062e-19 };
	cout << e << "\n";

	cout << setprecision(3) << "Set Pi as 3: " << pi << "\n";

}