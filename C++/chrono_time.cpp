#include "pch.h"
#include <ctime>
#include <chrono>

// C++ Time Library
// C++98: C���� ������ ctime�� Ȱ��. ==> �������� �ſ� ������.
// C++11: std::chrono ���̺귯�� ����. �ð� ��� Ȱ�� ����.
//  ==> ������ ������ ������ ctime���� �ξ� ��������.

// C++20: �� �����Ǿ� ��¥ �� �ð��� �ٷ�µ� �� Ȱ���� �� ����. 

using namespace std;

int main()
{
	// clock(), clock_t, time(), time_t
	// ��� ������ ������ ǥ���ȴ�.

	auto c_tick = clock(); // ��Ȯ���� �и��� ����
	auto t_tick = time(0); // ��Ȯ���� �� ����
	
	// literal surfix ����

	auto hour = 5h;
	auto min = 30min;
	auto sec = 10s;
	auto ms = 50ms;
	auto ns = 90ns;

	cout << hour.count() << " hour\n";
	cout << min.count() << " minutes\n";
	cout << sec.count() << " seconds\n";
	cout << ms.count() << " miliseconds\n";
	cout << ns.count() << " nano seconds\n";

	cout << (ms + ns).count() << " nano seconds \n";


	// implicit conversion

	chrono::seconds h_to_sec = 1h; // ok
	// chrono::hours sec_to_hour = 3000s; //  not ok conversion is not allowed if it cause data loss.

	std::cout << "1 hour to seconds: " << h_to_sec.count() << "\n";

	// explicit conversion with duration_cast
	auto ms_to_sec = chrono::duration_cast<chrono::seconds>(5043ms); // ����� ����ȯ�� ���� ĳ���� ����. 43ms�� �Ҵ´�.
	std::cout << "5043 ms to seconds: " << ms_to_sec.count() << "\n";
	auto ms_to_sec2 = chrono::duration_cast<chrono::seconds>(-5043ms);
	std::cout << "5043 ms to seconds: " << ms_to_sec2.count() << "\n";
	

	auto t1 = chrono::steady_clock::now();
	this_thread::sleep_for(2s);
	auto t2 = chrono::steady_clock::now();
	auto d = chrono::duration_cast<chrono::seconds>(t2 - t1);

	std::cout << d.count() << "\n";
	

	auto t3 = chrono::steady_clock::now();
	this_thread::sleep_for(2s);
	auto d2 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now().time_since_epoch() - 
		t3.time_since_epoch());

	std::cout << d2.count() << "\n";
}