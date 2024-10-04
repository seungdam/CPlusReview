#include <string>
#include <iostream>
#include <vector>
#include <cctype> // for character function : isupper,islower 

using namespace std;
bool bIsEqualString(const string& lhs, const string& rhs)
{
	if (lhs.length() != rhs.length()) return false;
	auto liter = lhs.cbegin();
	auto riter = rhs.cbegin();
	while (liter != lhs.cend() && riter != rhs.cend())
	{
		if (toupper(*liter) == toupper(*riter))
		{
			if (*liter != *riter) return false;
		}
		++liter; ++riter;
	}
	return true;
}

string exclaim(const string& str)
{
	auto iter_str = str.cbegin();
	auto retstr = ""s;
	retstr.resize(str.length()); // reduce overhead 

	auto iter_ret = retstr.begin();
	while (iter_str != str.end())
	{
		if (ispunct(*iter_str)) *iter_ret = '!';
		else *iter_ret = *iter_str;
		++iter_ret; ++iter_str;
	}
	return retstr;
}

int main()
{
	auto str = "ABCDEF"s;
	auto url = R"x(https:\\www.naver.com(you can use bracket inside here))x"s;
	cout << "URL: " << url << "\n\n";
	
	cout << "str: " << str << "\n";
	cout << "SubStr 0 ~ 3: " << str.substr(0, 3) << "\n\n";
	
	// c++17 �� if��

	if (auto ret = str.find('O'); ret == string::npos)
	{
		cout << "Find O: ";
		cout << "None O word in str\n";
	}

	cout << "str += [RHS]: ";
	str += "\033[38;5;153m [RHS] \033[0m";
	cout << str << "\n";

	cout << "Append GHIFFF: ";
	str.append("GHI", 0, 3); // ���� 2, 1�� ghi�� ���� �� ���꽺Ʈ���� ������ �� ����
	str.append(3,'F');
	cout << str << "\n\n";

	string abd{ "abd"};
	abd.insert(2, "c"); // �ش� �ε����� ���ʿ� �߰� 2�� �ε��� ==> d 
	cout << "After Insert C at index 2: \033[38;5;222m" << abd << "\033[0m\n";
	abd.insert(4, 3, 'F'); // index 4���� f�� 3�� �߰��ض�
	cout << "After Insert F 3 times at index 4: \033[38;5;222m" << abd << "\033[0m\n\n";

	// string iterator
	auto b = str.begin();
	auto cb = str.cbegin();
	auto crb = str.crbegin();

	// string iterator ���� ������ ��
	// string�� ��� ���ۿ� �����Ͱ� ���̴� ��������
	// insert�� ���� �������� ���� string ���۰� ���ο� ���۸� �Ҵ��� �����ϴ� ������ ��ģ�ٸ�
	// ���� iterator�� �ǹ̰� ��������.

	auto buffer = "Hellow"s;
	auto past_iter = begin(buffer);
	buffer.append(10, 'a');
	auto new_iter = begin(buffer);
	// past_iter != new_iter
	// past_iter�� ���̻� ��ȿ���� ���� ��
	cout << "Buffer: " << buffer << "\n";
	auto apos = buffer.find('a');
	buffer.erase(apos, 10);
	cout << "After Erase: " << buffer << "\n";

	buffer.replace(buffer.begin() + 2,buffer.end(),"WOW!!!!!");
	cout << "After Replace: " << buffer << "\n";
	cout << "After Assgin: " << buffer.assign("Assign") << "\n";
	// replace vs assign
	// assign: ��ü ������ ��ü
	// replace: �Ϻκи� ��ü

	// string <-> int
	// �������� atoi itoa �̷� �Լ� ���
	// �� stringstream���� ���ϴ�.
	// Ȥ�� to_string�� ���
	string ssss = R"())))(as()dsadas\\\()()()";
	std::cout << ssss;
	
	auto i = 171;
	auto convert_itos = to_string(i);
	auto convert_res = stoi(convert_itos, nullptr, 10);
	
	cout << "\n\nto_string: " << convert_itos << "\n";
	cout << "stoi:"  << convert_res << "\n";
	cout << "to_string type: " << typeid(convert_itos).name() << "\n";
	cout << "stoi type: " << typeid(convert_res).name() << "\n\n";
	size_t index{ 0 };
	auto int_str{"   345 567" };
	cout << dec << "stoi(  345 567): " << stoi(int_str, &index) << "\n";
	cout << "non-numeric char index: " << index << "\n\n";

	auto double_str{ "3.1415" };
	auto d = stold(double_str);
	

	auto sdata = str.data(); // same as str.c_str();
	cout << "str.data() type: " << typeid(sdata).name() << "\n";
	vector<int> v{5, 1};
	auto vdata = v.data();
	cout << "vector<int>(1,5).data() type: " << typeid(vdata).name() << "\n\n";


	// std::string::swap(str1,str2) --> �̵� �ø�ƽ�� ���
	// algorithm������ swap�� ����

	// std::string��ü���� Header�� ����. swap�� �� ��, �޸��� ����, ���ְ� �߻��ϴ� ���� �ƴ϶�
	// ��ü�� Header�� �̵��ϴ� ������ swapó��
	// Header���� count�� ���ڿ� pointer�� �������.

	auto sample_string = "The quick brown fox jumps over the lazy dog!!"s;

	for (const auto& i : sample_string)
	{
		cout << '\'' << i << "' [Attribute]: { ";
		if (isupper(i)) cout << "Upper ";
		else if (islower(i)) cout << "Lower ";

		if (isspace(i)) cout << "Space ";
		if (ispunct(i)) cout << "Punctuation ";
		cout << "}\n";
	}
	
	cout << exclaim("To be, or not to be, that is the question:");
}	

