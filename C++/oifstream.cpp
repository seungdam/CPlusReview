#include "pch.h"
#include <fstream>
#include <sstream>


using namespace std;

// [read]  for i
// [write] for o

int main()
{
	ofstream of{ "log.txt",ios::app };
	if (!of) return -1;

	for (int i = 0; i < 1'000'000; ++i)
	{
		cout << i << " " << flush;
		of << i << "\n" << flush;
		if (i == 10) terminate();
	}
}

//int main()
//{
//	string nfile{ "text.txt" };
//	ifstream file{nfile};
//	if (!file) return 0;
//
//	string full_data;
//	string word;
//	while (file >> word)
//	{
//		cout << word << " ";
//	}
//	file.close();
//	cout << "\n";
//
//	file.open(nfile);
//	while (getline(file, full_data))
//	{
//		cout << full_data;
//	}
//	file.close();
//	
//
//} 