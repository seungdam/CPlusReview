#include "pch.h"
#include "SharedClass.h"


int main()
{
	SharedClass sc("Hello");
	sc.print("sc");

	SharedClass sc2{ sc };
	sc2.print("sc2");
	sc.print("sc");

	SharedClass msc{ std::move(sc2) };
	msc.print("msc");
	sc2.print("sc2");
}