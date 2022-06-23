#pragma once



#include "Map.h"
#include "Paths.h"

#include <vector>
class PathFinder:public Map
{







private:
	std::vector<Paths>FootPrints;

	
public:



	using Map::Map;


	void addPath(PokemonNames Name, int x, int y);























};

