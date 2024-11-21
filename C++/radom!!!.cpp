#include "pch.h"

using namespace std;


/* *** random
 prng vs trng
 
 컴퓨터는 determinstic(결정론적)이기 때문에 진정한 random 값을 만들 수가 없음.
 그대신 pseudo-random-number-generating(prng)를 수행함.
 이는 특정 알고리즘을 통해 마치 랜덤한 난수를 제공하는 것처럼 수행한다.
 prng는 seed값을 제공받음으로써, 난수를 제공한다. 같은 seed를 가질 경우, 그 생성된 난수들은 동일한 패턴을 보인다.

 대표적인 prng로는 <stdlib>의 rand가 있다.
*/
#include <random>
int main()
{
	srand(time(0));
	cout << (rand() % 99) << "\n";


	// rand에 seed를 넘겨주는 함수 srand
	// 보편적으로 <ctime>의 time(0)를 통해 현재의 시간값을 넘겨주는 방법을 활용하나,
	// 해당 함수는 초 단위로 갱신되기 때문에 그 동안 생성되는 난수값에 관해 일정한 규칙을 파악당할 수 있음

	default_random_engine eng{}; // mondern C++에서 제공하는 prng object rand()를 wrapping한 것.


	mt19937 mt{}; // C++에서 제공하는 또다른 prng object/ 
	// 속도가 매우 빠르고 crypto를 보장한다. (다음 수를 예측하기 어려움)
	// 웬만하면 이걸 사용하는 것이 좋다.

	// uniform-distribution
	// 난수 값들을 실수 혹은 정수의 일정 범위 내로 리스케일링 하며, 모두 동일한 확률로 등장한다.

	uniform_int_distribution<int> uid{ 0,100 };
	// modern C++에서 제공하는 난수 범위 제한 functor
	// 들어오는 input값을 해당 범위로 리스케일링 해서 제공한다.
	uniform_real_distribution<float> fid{ 0.0,1.0 };


	// bernoulli-distribution
	// 난수 값을 boolean값으로 리스케일한다.
	// 50:50의 확률을 만들고 싶을 때 유용하다.
	bernoulli_distribution bd;
	cout << uid(mt) << "\n";
	cout << fid(mt) << "\n";
	cout << boolalpha << bd(mt) << "\n";

	// *** random-device
	// hardware를 통해 True Random Number를 생성한다.
	// system-entropy-data(프로세스id, cpu 온도 등을 스크램블 한 것)를 기반으로한다.
	// 하지만 이를 제공받지 못할 경우(컴파일러 혹은 시스템의 문제로), prng와 동일하게 동작한다.
	// 마찬가지로 functor의 형태로 구현되었으며, 퍼포먼스 제한으로 인해 난수 생성보다는 시드 생성으로 활용된다.

	random_device rd{};

	mt19937_64 rmt{ rd()};
	// *** recommend
	// 1. mt19937 사용
	// 2. rng 객체들은 static하게 활용 (복사/초기화하는데 오랜 시간이 걸리며, 다시 생성시 처음부터 동일한 일련의 난수를 재생성)


	// *** random_algorithm
	// 알고리즘에서 제공하는 유일한 난수 알고리즘 shuffle
	// legacy 버전인 random_shuffle이라는 함수도 존재한다. rand()를 활용해 구현함.
	// std::shuffle(range,rng object)
	
	// 기본적으로 std::swap을 활용해 구현한다.
	// swap(vec[i],vec[random_i])

	vector<int> nums{ 1,2,3,4,5 };
	shuffle(begin(nums), end(nums), rmt);

}