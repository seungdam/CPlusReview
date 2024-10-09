#include "pch.h"
#include <memory>

class GameObject
{
	int32 _id{ 0 };
public:
	GameObject() = default;
	GameObject(int32 id) : _id(id) {};
	GameObject(const GameObject& other) = default;
	GameObject(GameObject&& other) noexcept = default;

	int32 GetId() const { return _id; }
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
};


class Player : public GameObject
{
public:
	Player() : GameObject() {}
	Player(const Player& other) : GameObject(other.GetId()) {};
	Player(Player&& other) noexcept : GameObject(std::move(other)) {};

	virtual void Update(float elapsedTime) final { std::cout << "Player Update.\n"; };
	virtual void Render() final { std::cout << "Player Rendering.\n"; };
};

class Monster : public GameObject
{
public:
	Monster() : GameObject() {}
	Monster(const Monster& other) : GameObject(other.GetId()) {};
	Monster(Monster&& other) noexcept : GameObject(std::move(other)) {};

	virtual void Update(float elapsedTime) final { std::cout << "Monster Update.\n"; };
	virtual void Render() final { std::cout << "Monster Rendering.\n"; };
};

using UGameObject = std::unique_ptr<GameObject>;
// Factory Pattern 

UGameObject GobjFactory(int specific)
{
	if (1 == specific) return std::make_unique<Player>();
	else return std::make_unique<Monster>();

}

int main()
{
	// 일반적인 경우..
	std::vector<GameObject*> gobj;
	gobj.push_back(new Monster);
	gobj.push_back(new Player);
	gobj.push_back(new Monster);

	for (auto& i : gobj)
		i->Update(0.0f);

	// 모든 자원을 활용한 후, delete를 통해 해제해줘야 한다.. ==> unique_ptr로 대체할 수 있다는 것을 항상 생각하자.
	for (auto& i : gobj)
		delete i;

	std::cout << "\n\n";
	
	std::vector<UGameObject> gobj2;
	gobj2.push_back(std::make_unique<Monster>());
	gobj2.push_back(std::make_unique<Player>());
	gobj2.push_back(std::make_unique<Monster>());
	
	for (auto& i : gobj2)
		i->Update(0.0f);

	auto p1{ GobjFactory(1) };
	auto m1{ GobjFactory(2) };

	p1->Update(0.0f);
	m1->Update(0.1f);
}