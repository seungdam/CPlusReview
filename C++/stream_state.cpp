#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


// Stream State: stream 객체가 마지막으로 작업한 결과에 관한 반환을 해준다.
// ::good(): 성공 시 , return true
// ::fail(): 실패 시(Wrong formated data r/w), return true 
// ::bad(): 복구 불가능한 error 발생 시(Serious error such as disk), return true

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
	//	file이 빈 라인에 도달 했을 때, 이를 무시한다.
	//	즉 x의 값은 여전히 9를 유지하는 것
	//	ffile >> val;  ==> 마지막 new line에 관해 처리 x
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
			// cin은 flush를 제공하지 않는다. 그렇기 때문에
			// ignore()를 사용해 buffer에 저장된 오래된 stream들을 무시할 수 있다.
			cin.clear(); // buffer를 초기화하는 것이 아님. cin의 상태를 다시 valid하게 초기화
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> x;
		}
	}
}