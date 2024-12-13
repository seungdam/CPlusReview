#include "pch.h"
#include <typeinfo>

class Shape 
{
public:
	virtual void render() { std::cout << "Rendering Shape.\n"; }
};

class Circle : public Shape
{
public:
	void render() override { std::cout << "Rendering Circle\n"; }
};

class Triangle : public Shape
{
public:
	void render() override { std::cout << "Rendering Triangle\n"; }
};


int main()
{
	Shape* s = new Triangle;
	Shape* s2 = new Circle;

	std::cout << "Dynamic Type of s: " << typeid(*s).name() << "\n";
	s->render();
	std::cout << "Dynamic Type of s2: " << typeid(*s2).name() << "\n";
	s2->render();
}