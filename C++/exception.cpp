#include "pch.h"

using namespace std;


class MyException : public std::out_of_range
{
	string msg;
	char* cmsg = nullptr;
public:
	MyException(string str) : out_of_range(str), msg(str) {};
	MyException(char* str) : out_of_range(str),  cmsg(std::move(str)) {};

	virtual const char* what() const override
	{ 
		if (!msg.empty()) return msg.c_str(); 
							else return cmsg; 
	}
	virtual ~MyException() {}

};

int main()
{
	vector<int> v;
	try { cout << v.at(2) << "\n"; }
	catch (const exception& exp) { cout << exp.what() << "\n"; }


	try 
	{ 
		//cout << v.at(2); 
		throw MyException("hellow");
	}
	catch(const std::out_of_range oor)
	{
		cout << "std::out-of-range\n";
	}
	catch (const std::exception& exp)
	{
		cout << exp.what() << "\n";
	}
	catch (...)
	{
		cout << "unknown-type exception.\n";
	}

}