#pragma once

#include"Npc.h"

#include "PokemonNames.h"
class Paths :public Npc

{


private:
	PokemonNames Name;
	bool IsFound;


public:



	Paths();


	Paths(ALLEGRO_BITMAP* _Sprite, int x, int y, int h, int w,PokemonNames name,  Player * Player);









};

