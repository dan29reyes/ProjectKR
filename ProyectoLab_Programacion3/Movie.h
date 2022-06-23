#pragma once


#include "Npc.h";

#include "MessageBox.h";

#include <vector>

#include "Dialog.h"
#include"RigidBody.h"


class Movie
{



private:
	ALLEGRO_BITMAP* Background;

	ALLEGRO_BITMAP* PokemonSprite;
	ALLEGRO_BITMAP* TorrePizza;
	ALLEGRO_BITMAP* DescartesPng;
	ALLEGRO_BITMAP* MedievalPNG;
	Npc *Pokemon;
	ALLEGRO_TIMER* timer;
	ALLEGRO_TIMER* outsideTimer;
	bool MovieEnded;
	ALLEGRO_BITMAP* Book;
	ALLEGRO_BITMAP* KantPhoto;
	ALLEGRO_BITMAP* Pergamino;

	RigidBody PergaminoBody;




	Player* Input;

	ALLEGRO_FONT* Font;

	Dialog Npc_Dialogs;
	void load();
	

	


	bool DrawImg[4] = { false,false,false,false };



public :



	Movie();



	Movie(ALLEGRO_TIMER*,Player* _Input);






	void StartAnimattion();























};















