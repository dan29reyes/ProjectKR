#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "Body.h"
#include "string"


#ifndef MENU_H
#define MENU_H



class Menu {
private:

    ALLEGRO_FONT* fuente;
    ALLEGRO_COLOR blanco;
    ALLEGRO_COLOR azar;
    ALLEGRO_BITMAP* menu_null;
    ALLEGRO_BITMAP* menu_jugar;
    ALLEGRO_BITMAP* menu_salir;
    ALLEGRO_SAMPLE* efecto;
    ALLEGRO_SAMPLE* musica;
    ALLEGRO_SAMPLE_INSTANCE* insmusica;
    ALLEGRO_EVENT event;

    bool Show;
    int x, y;

    int buttons[1];

public:

    Menu();


    void setShow(bool item);
    

    void setMouseEvent(ALLEGRO_EVENT evt);
    bool ShowMenu();



};
#endif // !MENU_H
