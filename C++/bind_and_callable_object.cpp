#include "pch.h"
#include <functional>


using namespace std;

// *** Callable Object
// 1. lamda expression
// 2. std::bind return value
// 3. functor
// 4. c style function ptr 
// 5. non-member function



// 5. non-member function
bool compare_species(const string& rhs, const string& species) { return rhs == species; };

// 3. functor
class CmpSpecies
{
	string species;
public:
	bool operator()(const string& rhs) { return rhs == species; }
};


int main()
{
	vector<string> animals{ "Cat","Cat","Bird","Dog","Hamster" };
	vector<string> dest;

	// Cat�� �����ϱ�.
	copy_if(begin(animals), end(animals), back_inserter(dest), [](auto& r) 
		{ 
			return compare_species(r, "Cat");
		});

	for (auto i : dest) cout << i << " ";
	cout << "\n";


	// *** std::bind ���� �Լ��� �� �� Generic�ϰ� Ȱ���� �� �ֵ��� ����.
	// 4.  std::bind return value..
	auto cmp_cat = std::bind(compare_species, std::placeholders::_1, "Cat"); // �� ��° ���ڸ� Cat���� ����
	auto cmp_dog = std::bind(compare_species, std::placeholders::_1, "Dog");
	auto cmp_hms = std::bind(compare_species, std::placeholders::_1, "Hamster");

	//  ��ġ void func(string arg, string species = "Cat") �� ���·� ������ش�. 
	// �׸��� �̿� �ش��ϴ� Callable Object�� �����Ѵ�.

	
	// 2. C-Style Function ptr


	string species = "Cat";
	// 1. Lamda Function
	auto cmpLamda = [species](const string& rhs)->bool { return rhs == species; };


	//  ������ �Լ� Signature�� ���� Callable Object�� 
	// ������ Ÿ���� ���·� ��������. ==> Type-Erasing

	vector<std::function<bool(const string&)>> v;

	v.push_back(cmpLamda);
	v.push_back(cmp_cat);
	v.push_back(cmp_dog);
	v.push_back(cmp_hms);
	v.push_back(CmpSpecies{});



}