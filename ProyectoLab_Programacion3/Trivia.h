#pragma once
#include "Player.h"
#include <iostream>
#include <string>
#include <random>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>
#include <stdlib.h>
#ifndef TRIVIA_H
using std::cout;
using std::string;


#define TRIVIA_H

class Trivia{
private:
	int xr = 0, yr = 0, spins = 0, tipoS = 0;
	bool spinning = false, running = true;
	int ancho = 1024, alto = 768, xo = 0, y = 0, aux = 1;
	int resp = 0, xp = 0, mousex = 0, mousey = 0, segundos = 0;
	Player* Steve;
	int life = 0;

	ALLEGRO_FONT* font;
	ALLEGRO_FONT* font2;
	ALLEGRO_DISPLAY* ventana;
	ALLEGRO_TIMER* segundoTimer;
	ALLEGRO_TIMER* fps;
	ALLEGRO_EVENT_QUEUE* event_queue;
	
public:
	void drawball(ALLEGRO_BITMAP*, int, int);
	void dibujaroak(ALLEGRO_BITMAP*, int);
	void texto(string, int, int, int);
	void dibujaruleta(ALLEGRO_BITMAP*, int, int);
	Trivia(ALLEGRO_DISPLAY*, Player*);
	
	int  Ruleta();
	int ciencia();
	int arte();
	int historia();
	int politica();
	void reset();
};






#endif // !TRIVIA_H




