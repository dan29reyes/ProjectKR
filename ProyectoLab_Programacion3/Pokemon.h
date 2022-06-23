#pragma once


#include "Body.h"
class Pokemon:public Body
{


protected:

	int live;

	int atack;

	const char* nombre;


	ALLEGRO_FONT*font;



	ALLEGRO_BITMAP * LifeBar;


public:





	Pokemon();
	



	Pokemon(ALLEGRO_BITMAP* _sprite, int live, int atack, const char* _nombre, int _w, int _h);
	


	
















};

