#include "pch.h"

using namespace std;


int main()
{
	map<int, string> map_layer1;
	map_layer1.insert({ 1, "tile" });
	map_layer1.insert({ 2, "wall" });
	map_layer1.insert({ 3, "player" });
	
	map<int, string> map_layer2;
	map_layer2.insert({ 1, "tile" });
	map_layer2.insert({ 2, "wall" });
	map_layer2.insert({ 3, "monster" });
	map_layer2.insert({ 4, "player" });


	map<int, map<int, string>> rendering_layer;
	rendering_layer.insert({ 1, map_layer1 });
	rendering_layer.insert({ 2, map_layer2 });

	for (auto [level, maps] : rendering_layer)
	{
		cout << "[" << level << " Level]\n";
		for (auto [layer, obj] : maps) cout << layer << " : " << obj << "\n";
		cout << "\n";
	}


}