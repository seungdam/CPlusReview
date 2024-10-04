#include <fstream>
#include <iostream>
#include <string>
//��Ʈ���� ����
//��Ʈ���� �����͸� �а� ���� �� ���Ǵ� �߻�ȭ�� �����Դϴ�.
// ��Ʈ���� ���������� ���۸� ����Ͽ� ȿ�������� �����͸� ó���մϴ�.
// ���۴� �����͸� �ӽ÷� �����ϴ� �޸� ��������, 
// �Է°� ��� �۾��� ����ȭ�ϴ� �� �߿��� ������ �մϴ�.


//��Ʈ�� ������ ����
//�Է� ���� : �Է� ��Ʈ��(std::istream)�� �����͸� ���� �� ���۸� ����մϴ�.���� ���, std::cin�� ����ڰ� �Է��� �����͸� ���ۿ� �����ϰ�, ���α׷��� �ʿ�� �� �� ���ۿ��� �����͸� �о�ɴϴ�.
//��� ���� : ��� ��Ʈ��(std::ostream)�� �����͸� �� �� ���۸� ����մϴ�.���� ���, std::cout�� ����� �����͸� ���ۿ� �����ϰ�, ���۰� ���� ���ų� �÷���(flush) ����� ���� �� �Ѳ����� ����մϴ�.

int main()
{
	char a{ 0 };


	// line-oriented input: \n �������� read�� ��� ������.
	//while (std::cin.get(a)) // �Է��� ����ޱ� ���ؼ� esc�� ��������.
	//{
	//	std::cout.put(a); 
	//}
	char c;
	std::cin.get(c);
	std::cout.put(c);
	std::cout << "\n";

	char buff[512]{ 0 };
	// *** fstream read, write
	// stream�� ���� buffer ������ �̷������ ���� �ƴ϶� �츮�� buffer�� �����ؾ���.
	// network application�� ���� ��Ŷ �ۼ��� ���α׷����� Ȱ���ϴ� ��İ� ����.

	// file mode
	// 1. read files default ==> text mode(character stored data as ascII )
	//		 �� binary mode: stored data as a single binary number 
	//        text mode ==> 42�� ���� '4'�� '2'�� ASCII ���ڰ����� ����
	//        binary mode ==> 42�� ���� ���� 42�� �������� ���·� ����
	//	���̳ʸ� ���� ����� low level ���·� �����ϱ� ������ ��� �������� ������ �߻���ų Ȯ���� ����.
	//  Ex) ���� OS���� �ٸ� ������ ����� ���,
	//		�ٸ� OS�� ����� ���, 
	//		���� file�� ���� �ٸ� format���� ó���� ���...
	//  ���� img,video �����ؼ� �̷� ���·� �о�´�.
	// 2. write files defualt ==> turnacate mode (all the data erase, it will be overwritten.)
	//       �� ios::app => �̾ ���� ��Ʈ����ũ �÷���.

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