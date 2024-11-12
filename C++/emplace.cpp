#include "pch.h"

using namespace std;
// *** C++11 emplace
// 컨테이너에 원소를 추가하는 또 다른 방법 emplace
// insert, push_back은 우리가 컨테이너에 적절한 타입의 값을 넣는다는 가정하에 진행된다.
// 그리고 이미 존재하는 값에 대해 복사해서 추가한다. --> 즉 기존 값을 재사용하는 것이 가능하다.
// 즉, 일부만 복사되는 상황이 발생하거나, 부적절한 타입을 추가하도록하면 예외가 발생한다는 것이다.

// 반면 emplace는 복사하는 것이아니라 생성하고 이를 집어 넣는다. 즉 복사생성자가 호출되지 않는다.
// 컨테이너에 크기가 큰 객체를 관리할 경우 유의미한 차이를 볼 수 있다.

struct object
{
	int id;
	string type;
	bool available;
};
int main()
{
	vector<object> objs;

	objs.push_back({0, "none", false}); // 임시 객체 생성 -> 복사 생성 및 추가 -> 임시 객체 파괴
	objs.emplace(objs.begin(), 1, "player", true); // 복사 생성 X, 기본 생성 O
	// objs.emplace_back

	// 이때 고유 키를 가지는 연관 컨테이너 한정해서 emplace가 다소 다르게 동작한다.
	// 이들은 emplace를 호출하더라도, 임시 객체를 생성하고 해당 객체를 기반으로 check를 수행한다.
	// 그 대신 try_emplace를 사용한다.
	// try_emplace는 객체 생성 이전에 중복 체크를 수행한다.
	// 즉 중복된 키가 존재한다면 아무 것도 수행하지 않는다는 것이다.
	map<string, object> m;
	auto [iter, success] = m.try_emplace("None", 0, "none", false);

}
