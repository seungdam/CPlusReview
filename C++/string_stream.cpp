#include "pch.h"
#include <fstream>
#include <sstream>
#include <cctype>

// 문자열 작업을 위한 stream 함수들을 제공하는 stringstream 클래스
// string 클래스를 wrapping 하여, 마치 stream처럼 동작하는 것처럼 보임.
using namespace std;

struct language
{
	string lang;
	string designer;
	int data;
	friend ostream& operator<<(ostream& os, const language& l)
	{
		os << l.lang << ", " << l.designer << ", " << l.data;
		return os;
	}
};


int main()
{
	auto file = fstream {"languages.txt", ios::in};
	auto line = ""s;
	auto ss =  stringstream{};
	auto v = vector<language>();
	
	while (getline(file, line))
	{
		language l;
		string data;
		ss.str("");
		ss.clear();

		ss << line;
		ss >> l.lang;
		while (ss >> data)
		{
			if (isdigit(data[0]))
			{
				l.data = stoi(data);
				break;
			}
			else
			{
				l.designer += data;
				l.designer += " ";
			}
		}
		if (!l.designer.empty()) l.designer.pop_back();
		v.push_back(l);
	}

	for (const auto& i : v) cout << i << "\n";
}