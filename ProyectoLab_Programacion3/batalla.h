#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <random>
#include "Player.h"

#ifndef BATALLA_H
#define BATALLA_H
using namespace std;
class batalla {
public:
	batalla(ALLEGRO_DISPLAY*, Player*);
	int mainBattle(ALLEGRO_DISPLAY*, Player*);
private:
	int ancho = 1024, alto = 768;
	ALLEGRO_DISPLAY* ventana;
	ALLEGRO_TIMER* segundoTimer;
	ALLEGRO_TIMER* fps;
	
	Player* Steve;
	int life = 0;
	void texto(string, int, int, int);
	void reset();
};
#endif 