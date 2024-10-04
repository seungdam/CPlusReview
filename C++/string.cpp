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
	
	// c++17 식 if문

	if (auto ret = str.find('O'); ret == string::npos)
	{
		cout << "Find O: ";
		cout << "None O word in str\n";
	}

	cout << "str += [RHS]: ";
	str += "\033[38;5;153m [RHS] \033[0m";
	cout << str << "\n";

	cout << "Append GHIFFF: ";
	str.append("GHI", 0, 3); // 뒤의 2, 1은 ghi를 더할 때 서브스트링만 더해줄 수 있음
	str.append(3,'F');
	cout << str << "\n\n";

	string abd{ "abd"};
	abd.insert(2, "c"); // 해당 인덱스의 앞쪽에 추가 2번 인덱스 ==> d 
	cout << "After Insert C at index 2: \033[38;5;222m" << abd << "\033[0m\n";
	abd.insert(4, 3, 'F'); // index 4번에 f를 3번 추가해라
	cout << "After Insert F 3 times at index 4: \033[38;5;222m" << abd << "\033[0m\n\n";

	// string iterator
	auto b = str.begin();
	auto cb = str.cbegin();
	auto crb = str.crbegin();

	// string iterator 사용시 주의할 점
	// string의 모든 버퍼에 데이터가 차이는 과정에서
	// insert와 같은 동작으로 인해 string 버퍼가 새로운 버퍼를 할당해 이전하는 과정을 거친다면
	// 기존 iterator는 의미가 없어진다.

	auto buffer = "Hellow"s;
	auto past_iter = begin(buffer);
	buffer.append(10, 'a');
	auto new_iter = begin(buffer);
	// past_iter != new_iter
	// past_iter는 더이상 유효하지 않은 것
	cout << "Buffer: " << buffer << "\n";
	auto apos = buffer.find('a');
	buffer.erase(apos, 10);
	cout << "After Erase: " << buffer << "\n";

	buffer.replace(buffer.begin() + 2,buffer.end(),"WOW!!!!!");
	cout << "After Replace: " << buffer << "\n";
	cout << "After Assgin: " << buffer.assign("Assign") << "\n";
	// replace vs assign
	// assign: 전체 문장을 대체
	// replace: 일부분만 대체

	// string <-> int
	// 이전에는 atoi itoa 이런 함수 사용
	// 걍 stringstream쓰면 편하다.
	// 혹은 to_string을 사용
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


	// std::string::swap(str1,str2) --> 이동 시멘틱을 사용
	// algorithm에서도 swap을 제공

	// std::string객체들은 Header가 존재. swap을 할 때, 메모리의 복사, 이주가 발생하는 것이 아니라
	// 객체의 Header만 이동하는 것으로 swap처리
	// Header에는 count와 문자열 pointer를 담고있음.

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

