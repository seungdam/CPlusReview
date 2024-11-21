#include "pch.h"

using namespace std;

int main()
{
	string str{ "abc" };

	do
	{
		cout << str << "\n";
	} while (next_permutation(begin(str), end(str)));

	cout << "\n\n";

	string str2{ "fed" };
	do
	{
		cout << str2 << "\n";
	} while (prev_permutation(begin(str2), end(str2)));

}