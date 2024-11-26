#include "pch.h"
#include <bitset> // since c++11


using namespace std;

// bit 연산을 좀 더 직관적이고 안전하게 수행하기 위해 등장한 라이브러리

int main()
{
	// <- index 방향
	// mlb 10011001 msb
	bitset<8> b1{ "10011001" };
	bitset<8> b2{ 0b1001'1001 };
	bitset<8> b3{ 0x99 };

	
	cout << b1 << " " << b2 << " " << b3 << "\n";
	cout << b1.size() << " " << b2.size() << " " << b3.size() << "\n";
	try
	{
		auto retval = b1.test(7);
	}
	catch (...)
	{
		cout << "out-of-range";
	}


	// bit modify as true
	b1.set(); // set all bit true
	b1.set(6); // set 6 index bit as true
	b1.set(0, true); // can give index & flag
	
	// bit modify as false
	b2.reset(); // set all bit false
	// reset(index);

	// bit modify as flip

	b3.flip(); // flip all the bits


}