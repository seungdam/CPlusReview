#include <fstream>
#include <iostream>
#include <string>
//스트림과 버퍼
//스트림은 데이터를 읽고 쓰는 데 사용되는 추상화된 개념입니다.
// 스트림은 내부적으로 버퍼를 사용하여 효율적으로 데이터를 처리합니다.
// 버퍼는 데이터를 임시로 저장하는 메모리 공간으로, 
// 입력과 출력 작업을 최적화하는 데 중요한 역할을 합니다.


//스트림 버퍼의 역할
//입력 버퍼 : 입력 스트림(std::istream)은 데이터를 읽을 때 버퍼를 사용합니다.예를 들어, std::cin은 사용자가 입력한 데이터를 버퍼에 저장하고, 프로그램이 필요로 할 때 버퍼에서 데이터를 읽어옵니다.
//출력 버퍼 : 출력 스트림(std::ostream)은 데이터를 쓸 때 버퍼를 사용합니다.예를 들어, std::cout은 출력할 데이터를 버퍼에 저장하고, 버퍼가 가득 차거나 플러시(flush) 명령이 있을 때 한꺼번에 출력합니다.

int main()
{
	char a{ 0 };


	// line-oriented input: \n 이전까지 read를 계속 수행함.
	//while (std::cin.get(a)) // 입력을 종료받기 위해선 esc를 눌러야함.
	//{
	//	std::cout.put(a); 
	//}
	char c;
	std::cin.get(c);
	std::cout.put(c);
	std::cout << "\n";

	char buff[512]{ 0 };
	// *** fstream read, write
	// stream에 의해 buffer 관리가 이루어지는 것이 아니라 우리가 buffer를 제공해야함.
	// network application과 같은 패킷 송수신 프로그램에서 활용하는 방식과 같음.

	// file mode
	// 1. read files default ==> text mode(character stored data as ascII )
	//		 ㄴ binary mode: stored data as a single binary number 
	//        text mode ==> 42에 관해 '4'와 '2'를 ASCII 문자값으로 저장
	//        binary mode ==> 42에 관해 숫자 42의 이진수의 형태로 저장
	//	바이너리 모드는 상당히 low level 형태로 동작하기 때문에 사용 과정에서 오류를 발생기킬 확률이 높음.
	//  Ex) 같은 OS에서 다른 세팅을 사용할 경우,
	//		다른 OS를 사용할 경우, 
	//		같은 file에 관해 다른 format으로 처리할 경우...
	//  보통 img,video 관련해서 이런 형태로 읽어온다.
	// 2. write files defualt ==> turnacate mode (all the data erase, it will be overwritten.)
	//       ㄴ ios::app => 이어서 쓰기 비트마스크 플래그.

	std::ifstream in("text.txt");
	if (!in) return 0;




	in.read(buff, 512);
	auto rsize = in.gcount(); // get how many bytes that i read
	std::string s(buff);
	std::cout << rsize << " Bytes read.\n";
	std::cout << s;
	in.close();

	std::ofstream out{"text.txt", std::ios::app};
	out << "append some data.\n";
	out.close();

	std::fstream ffile{"text.txt",std::ios::in | std::ios::out};

	

}