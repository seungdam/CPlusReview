#include "pch.h"
#include <ctime>
#include <chrono>

// C++ Time Library
// C++98: C언어로 구현된 ctime을 활용. ==> 디자인이 매우 안좋음.
// C++11: std::chrono 라이브러리 등장. 시간 기능 활용 가능.
//  ==> 복잡한 문법을 띄지만 ctime보단 훨씬 발전됐음.

// C++20: 더 개선되어 날짜 및 시간을 다루는데 잘 활용할 수 있음. 

using namespace std;

int main()
{
	// clock(), clock_t, time(), time_t
	// 모두 정수의 값으로 표현된다.

	auto c_tick = clock(); // 정확도는 밀리초 단위
	auto t_tick = time(0); // 정확도는 초 단위
	
	// literal surfix 제공

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
	auto ms_to_sec = chrono::duration_cast<chrono::seconds>(5043ms); // 명시적 형변환을 통해 캐스팅 가능. 43ms는 잃는다.
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