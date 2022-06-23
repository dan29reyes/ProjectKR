#include "Menu.h";
#include "MessageBox.h";

Menu::Menu(){
    fuente = al_load_font("fuente/pokemon_pixel_font.ttf", 70, 0);;
    blanco = al_map_rgb(255, 255, 255);
    azar = al_map_rgb(255, 50, 65);
    menu_null = al_load_bitmap("imagenes/menu_null.png");
    menu_jugar = al_load_bitmap("imagenes/menu_jugar.png");
    menu_salir = al_load_bitmap("imagenes/menu_salir.png");
    efecto = al_load_sample("sonidos/efecto_menu.wav");
    musica = al_load_sample("sonidos/menu.wav");
    insmusica = al_create_sample_instance(musica);
    buttons[1] = 0;
    al_set_sample_instance_playmode(insmusica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(insmusica, al_get_default_mixer());
    Show = true;
}

void Menu::setShow(bool item){
	Show = true;
}

void Menu::setMouseEvent(ALLEGRO_EVENT evt) {
    event = evt;
}

bool Menu::ShowMenu() {
    if (Show) {
        if (buttons[0] == 0)
            al_draw_bitmap(menu_null, 0, 0, 0);
        else if (buttons[0] == 1)
            al_draw_bitmap(menu_jugar, 0, 0, 0);
        else
            al_draw_bitmap(menu_salir, 0, 0, 0);

        if ( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            x = event.mouse.x;
            y = event.mouse.y;
            if (x >= 193 && x <= 874 && y >= 347 && y <= 462) {
                buttons[0] = 1;
                if (event.mouse.button & 1) {
                    //empezar
                    Show = false;
                    al_destroy_bitmap(menu_null);
                    al_destroy_bitmap(menu_salir);
                    al_destroy_bitmap(menu_jugar);
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    return false;
                }
                al_play_sample(efecto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            }
            else {
                if (x >= 193 && x <= 874 && y >= 495 && y <= 610) {
                    buttons[0] = 2;
                    if (event.mouse.button & 1) {
                        return false;
                    }
                    al_play_sample(efecto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                }
                else {
                    buttons[0] = 0;
                }
            }
        }
    }
    return true;
}