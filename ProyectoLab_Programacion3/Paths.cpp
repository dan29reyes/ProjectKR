#include "Paths.h"

Paths::Paths():Npc(NULL,0,0,0,0,nullptr){}

Paths::Paths(ALLEGRO_BITMAP* _Sprite, int x, int y, int h, int w, PokemonNames name,Player*Player) :Npc(_Sprite,x, y,h,w, Player){
	Name = name;
	//Tener cuidado con player
}