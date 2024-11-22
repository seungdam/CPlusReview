#include "pch.h"

using namespace std;

int main()
{
	vector<int> v;
	try { cout << v.at(2) << "\n"; }
	catch (const exception exp) { cout << exp.what() << "\n"; }
}