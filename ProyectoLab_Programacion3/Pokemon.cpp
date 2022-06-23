#include "Pokemon.h"

Pokemon::Pokemon(){}

Pokemon::Pokemon(ALLEGRO_BITMAP* _sprite, int live, int atack, const char* _nombre, int _w, int _h){
	Sprite = _sprite;
	this->live = live;
	this->atack = atack;
	nombre = _nombre;
	x = 0;
	y = 0;
}