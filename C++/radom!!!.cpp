#include "pch.h"

using namespace std;


/* *** random
 prng vs trng
 
 ��ǻ�ʹ� determinstic(��������)�̱� ������ ������ random ���� ���� ���� ����.
 �״�� pseudo-random-number-generating(prng)�� ������.
 �̴� Ư�� �˰����� ���� ��ġ ������ ������ �����ϴ� ��ó�� �����Ѵ�.
 prng�� seed���� �����������ν�, ������ �����Ѵ�. ���� seed�� ���� ���, �� ������ �������� ������ ������ ���δ�.

 ��ǥ���� prng�δ� <stdlib>�� rand�� �ִ�.
*/
#include <random>
int main()
{
	srand(time(0));
	cout << (rand() % 99) << "\n";


	// rand�� seed�� �Ѱ��ִ� �Լ� srand
	// ���������� <ctime>�� time(0)�� ���� ������ �ð����� �Ѱ��ִ� ����� Ȱ���ϳ�,
	// �ش� �Լ��� �� ������ ���ŵǱ� ������ �� ���� �����Ǵ� �������� ���� ������ ��Ģ�� �ľǴ��� �� ����

	default_random_engine eng{}; // mondern C++���� �����ϴ� prng object rand()�� wrapping�� ��.


	mt19937 mt{}; // C++���� �����ϴ� �Ǵٸ� prng object/ 
	// �ӵ��� �ſ� ������ crypto�� �����Ѵ�. (���� ���� �����ϱ� �����)
	// �����ϸ� �̰� ����ϴ� ���� ����.

	// uniform-distribution
	// ���� ������ �Ǽ� Ȥ�� ������ ���� ���� ���� �������ϸ� �ϸ�, ��� ������ Ȯ���� �����Ѵ�.

	uniform_int_distribution<int> uid{ 0,100 };
	// modern C++���� �����ϴ� ���� ���� ���� functor
	// ������ input���� �ش� ������ �������ϸ� �ؼ� �����Ѵ�.
	uniform_real_distribution<float> fid{ 0.0,1.0 };


	// bernoulli-distribution
	// ���� ���� boolean������ ���������Ѵ�.
	// 50:50�� Ȯ���� ����� ���� �� �����ϴ�.
	bernoulli_distribution bd;
	cout << uid(mt) << "\n";
	cout << fid(mt) << "\n";
	cout << boolalpha << bd(mt) << "\n";

	// *** random-device
	// hardware�� ���� True Random Number�� �����Ѵ�.
	// system-entropy-data(���μ���id, cpu �µ� ���� ��ũ���� �� ��)�� ��������Ѵ�.
	// ������ �̸� �������� ���� ���(�����Ϸ� Ȥ�� �ý����� ������), prng�� �����ϰ� �����Ѵ�.
	// ���������� functor�� ���·� �����Ǿ�����, �����ս� �������� ���� ���� �������ٴ� �õ� �������� Ȱ��ȴ�.

	random_device rd{};

	mt19937_64 rmt{ rd()};
	// *** recommend
	// 1. mt19937 ���
	// 2. rng ��ü���� static�ϰ� Ȱ�� (����/�ʱ�ȭ�ϴµ� ���� �ð��� �ɸ���, �ٽ� ������ ó������ ������ �Ϸ��� ������ �����)


	// *** random_algorithm
	// �˰��򿡼� �����ϴ� ������ ���� �˰��� shuffle
	// legacy ������ random_shuffle�̶�� �Լ��� �����Ѵ�. rand()�� Ȱ���� ������.
	// std::shuffle(range,rng object)
	
	// �⺻������ std::swap�� Ȱ���� �����Ѵ�.
	// swap(vec[i],vec[random_i])

	vector<int> nums{ 1,2,3,4,5 };
	shuffle(begin(nums), end(nums), rmt);

}