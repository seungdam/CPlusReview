#include "pch.h"
#include "SharedClass.h"


int main()
{
	SharedClass sc("sc","Hello");  // 0
	SharedClass sc_copy{ sc };  // 1
	SharedClass sc_copy2 = sc_copy; // 2

	SharedClass msc{ std::move(sc_copy) };
}