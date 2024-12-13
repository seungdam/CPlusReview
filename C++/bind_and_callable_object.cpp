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

	// Cat만 복사하기.
	copy_if(begin(animals), end(animals), back_inserter(dest), [](auto& r) 
		{ 
			return compare_species(r, "Cat");
		});

	for (auto i : dest) cout << i << " ";
	cout << "\n";


	// *** std::bind 위의 함수를 좀 더 Generic하게 활용할 수 있도록 하자.
	// 4.  std::bind return value..
	auto cmp_cat = std::bind(compare_species, std::placeholders::_1, "Cat"); // 두 번째 인자를 Cat으로 고정
	auto cmp_dog = std::bind(compare_species, std::placeholders::_1, "Dog");
	auto cmp_hms = std::bind(compare_species, std::placeholders::_1, "Hamster");

	//  마치 void func(string arg, string species = "Cat") 의 형태로 만들어준다. 
	// 그리고 이에 해당하는 Callable Object를 리턴한다.

	
	// 2. C-Style Function ptr


	string species = "Cat";
	// 1. Lamda Function
	auto cmpLamda = [species](const string& rhs)->bool { return rhs == species; };


	//  동일한 함수 Signature를 가진 Callable Object를 
	// 동일한 타입의 형태로 관리하자. ==> Type-Erasing

	vector<std::function<bool(const string&)>> v;

	v.push_back(cmpLamda);
	v.push_back(cmp_cat);
	v.push_back(cmp_dog);
	v.push_back(cmp_hms);
	v.push_back(CmpSpecies{});



}