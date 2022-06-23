#include <iostream>
#include <Windows.h>
#include <random>
#include "batalla.h"

ALLEGRO_FONT* font;
int aux=1, xash = 0, poke = 5, x2 = 0, x3 = 0, resp = 0, xj2 = 768, hits1 = 0, hits2 = 0;
int yj2 = 60, xj1 = 230, yj1 = 200, first = 0, hpj1 = 0, hpj2 = 0;;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr1(0, 4);
std::uniform_int_distribution<> distr2(0, 4);
int rnd1 = distr1(gen);
int rnd2 = distr2(gen);


struct pokemon {
	ALLEGRO_BITMAP* negra;
	ALLEGRO_BITMAP* blast;
	
	bool blastdibujar = false;
	void DrawNormal(int x, int y) {
		
		if (blastdibujar==true) {
			al_draw_bitmap(negra, x, y, 0);
		}
	}
	
	pokemon(const char* name) {
		negra = al_load_bitmap(name);
	}

	pokemon() {	
		negra = al_load_bitmap("imagenes/Pokemones.png");
	}
	void draw(int x, int y) {
		al_draw_bitmap_region(negra,200*rnd1, 175.47*rnd2, 200, 175.47,x,y,0);
	}
};

batalla::batalla(ALLEGRO_DISPLAY* display, Player* _Steve) {
	ventana = display;
	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "Trivia");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);
}

int batalla::mainBattle(ALLEGRO_DISPLAY* display, Player* _Steve) {
	reset();
	Steve = _Steve;
	ALLEGRO_EVENT_QUEUE* event_queue;
	event_queue = al_create_event_queue();
	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 60);
	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(fps);
	bool terminado = false;
	life = Steve->getVida();
	font = al_load_ttf_font("imagenes/pokefuente.ttf", 34, 0);
	
	//Imagenes
	ALLEGRO_BITMAP* hpbars[2];
	hpbars[0] = al_load_bitmap("imagenes/hpbar.png");
	hpbars[1] = al_load_bitmap("imagenes/hpbar.png");
	ALLEGRO_BITMAP* fondo = al_load_bitmap("imagenes/Tile_BatallaEnemy.png");
	ALLEGRO_BITMAP* ash = al_load_bitmap("imagenes/Presentation.png");
	ALLEGRO_BITMAP* yeye = al_load_bitmap("imagenes/DialogBar.bmp");
	ALLEGRO_BITMAP* pokeball = al_load_bitmap("imagenes/pokebola.png");
	ALLEGRO_BITMAP* ally = al_load_bitmap("imagenes/blast.png");
	ALLEGRO_BITMAP* enemy = al_load_bitmap("imagenes/Pokemones.png");
	
	//Musica batalla
	ALLEGRO_SAMPLE* musica = al_load_sample("imagenes/pelea.mp3");
	ALLEGRO_SAMPLE_INSTANCE* insmusica = al_create_sample_instance(musica);
	al_set_sample_instance_playmode(insmusica, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(insmusica, al_get_default_mixer());
	
	//Musica Racionalista
	ALLEGRO_SAMPLE* racional = al_load_sample("imagenes/Racionalista.mp3");
	ALLEGRO_SAMPLE_INSTANCE* inracional = al_create_sample_instance(racional);
	al_set_sample_instance_playmode(inracional, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(inracional, al_get_default_mixer());
	
	//Musica Empirista
	ALLEGRO_SAMPLE* empirista = al_load_sample("imagenes/Empirista.mp3");
	ALLEGRO_SAMPLE_INSTANCE* inempirista = al_create_sample_instance(empirista);
	al_set_sample_instance_playmode(inempirista, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(inempirista, al_get_default_mixer());

	//Variables
	bool animation=true;
	pokemon negra;
	
	//Timers
	ALLEGRO_TIMER* timer;
	ALLEGRO_TIMER* poketimer;
	ALLEGRO_TIMER* wait;
	ALLEGRO_TIMER* attack;
	timer = al_create_timer(1.0/60);
	poketimer = al_create_timer(1.0 / 60);
	wait = al_create_timer(1.0 / 60);
	attack = al_create_timer(1.0 / 60);
	al_start_timer(timer);
	al_start_timer(poketimer);
	al_start_timer(wait);
	al_start_timer(attack);
	pokemon blast("imagenes/blast.png");
	while (true)
	{ 
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		ALLEGRO_KEYBOARD_STATE KeyState;
		al_get_keyboard_state(&KeyState);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (aux <= 8) {
			al_play_sample_instance(insmusica);
			al_set_sample_instance_gain(insmusica, 0.3);
		}
		else if (hpj1 < hpj2 && aux > 8) {
			al_stop_sample_instance(insmusica);
			al_play_sample_instance(inempirista);
			al_set_sample_instance_gain(inempirista, 0.3);
			Steve->setVida(life);
			Steve->setMedal(2);
		}
		else if (hpj1 > hpj2 && aux > 8) {
			al_stop_sample_instance(insmusica);
			al_play_sample_instance(inracional);
			al_set_sample_instance_gain(inracional, 0.3);
			Steve->setVida(life);
		}
		
		al_draw_bitmap(fondo, 0, 0, 0);
		al_draw_bitmap_region(ash, xash*225,0, 225, 177,x2,390, NULL);
		al_draw_bitmap(yeye, 0, 528, 0);
		al_draw_bitmap_region(pokeball, poke * 36, 0, 36, 36, x3, 356, NULL);
		if (hpj1 < 5 && aux < 9) {
			blast.DrawNormal(xj1, yj1);
			al_draw_bitmap_region(hpbars[0], hpj1 * 273, 0, 273, 96, 726, 412, NULL);
		}
		else if (hpj1 > hpj2 && aux > 8) {
			texto("!!!Tu pokemon ha sido derrotado, ganan los Empiristas!!!", 255, 200, 688);
			texto("!!!Presiona Tecla Escape para salir!!!", 255, 260, 724);
			al_draw_tinted_bitmap(ally, al_map_rgb(255, 0, 0), xj1, yj1, 0);
			terminado = true;
		}
		
		if (hpj2 < 5 && aux < 9) {
			negra.draw(xj2, yj2);
			al_draw_bitmap_region(hpbars[1], hpj2 * 273, 0, 273, 96, 140, 25, NULL);
		}
		else if (hpj1 < hpj2 && aux > 8) {
			texto("!!!Derrotaste al pokemon enemigo, ganan los Racionalistas!!!", 255, 160, 688);
			texto("!!!Presiona Tecla Escape para salir!!!", 255, 260, 724);
			al_draw_tinted_bitmap_region(enemy, al_map_rgb(230, 0, 0), 200 * rnd1, 175.47 * rnd2, 200, 175.47, xj2, yj2, 0);
			terminado = true;
		}
		
		if (hpj1 == hpj2 && aux > 8) {
			texto("!!!El resultado termina en un empate, vuelve a intentarlo!!!", 255, 200, 688);
			texto("!!!Presiona Tecla Escape para salir!!!", 255, 260, 724);
			al_draw_tinted_bitmap(ally, al_map_rgb(255, 0, 0), xj1, yj1, 0);
			al_draw_tinted_bitmap_region(enemy, al_map_rgb(230, 0, 0), 200 * rnd1, 175.47 * rnd2, 200, 175.47, xj2, yj2, 0);
			Steve->setVida(life);
			terminado = true;
		}
		
		if (terminado == true) {
			if (al_key_down(&KeyState, ALLEGRO_KEY_ESCAPE)) {
				al_stop_sample_instance(insmusica);
				al_stop_sample_instance(inracional);
				al_stop_sample_instance(inempirista);
				return 0;
			}
		}
		
		if (hpj1 < 5 && hpj2 < 5) {
			if (resp == 0) {
				if (aux == 1) {
					texto("Para algunos de los siguientes filosofos, el criterio de verdad es la evidencia sensible: ", 255, 24, 676);
					texto("A) Empiristas", 0, 36, 559);
					texto("B) Criticistas", 0, 436, 559);
					texto("C) Racionalistas", 0, 36, 595);
					texto("D) Dogmaticos", 0, 436, 595);
				}
				else if (aux == 2) {
					texto("De las siguientes, una de ellas es la corriente filosofica que en general tiende a negar la", 255, 24, 676);
					texto("posibilidad de la metafisica y a sostener que hay conocimiento únicamente de los fenomenos", 255, 24, 710);
					texto("A) Racionalistas", 0, 36, 559);
					texto("B) Empiristas", 0, 436, 559);
					texto("C) Escolasticos", 0, 36, 595);
					texto("D) Escepticos", 0, 436, 595);
				}
				else if (aux == 3) {
					texto("Para unos de los siguientes filosofos, la experiencia como unica fuente del conocimiento", 255, 24, 676);
					texto("A) Epistemologos", 0, 36, 559);
					texto("B) Racionalistas", 0, 436, 559);
					texto("C) Empiristas", 0, 36, 595);
					texto("D) Escepticos", 0, 436, 595);
				}
				else if (aux == 4) {
					texto("Filosofos para quienes la unica fuente del conocimiento es la razon", 255, 24, 676);
					texto("A) Epistemologos", 0, 36, 559);
					texto("B) Racionalistas", 0, 436, 559);
					texto("C) Empiristas", 0, 36, 595);
					texto("D) Escepticos", 0, 436, 595);
				}
				else if (aux == 5) {
					texto("Filosofos que postulan las ideas innatas en el sujeto", 255, 24, 676);
					texto("A) Empiristas", 0, 36, 559);
					texto("B) Idealistas", 0, 436, 559);
					texto("C) Racionalistas", 0, 36, 595);
					texto("D) Innatistas", 0, 436, 595);
				}
				else if (aux == 6) {
					texto("De los siguientes filosofos selecciones el que no se considera Racionalista", 255, 24, 676);
					texto("A) David Hume", 0, 36, 559);
					texto("B) John Locke", 0, 436, 559);
					texto("C) Nicolas Malebranch", 0, 36, 595);
					texto("D) Francis Bacon", 0, 436, 595);
				}
				else if (aux == 7) {
					texto("Es la doctrina que establece que todos nuestros conocimientos provienen de la razon", 255, 24, 676);
					texto("A) Empirismo", 0, 36, 559);
					texto("B) Criticismo", 0, 436, 559);
					texto("C) Racionalismo", 0, 36, 595);
					texto("D) Epistemologia", 0, 436, 595);
				}
				else if (aux == 8) {
					texto("Uno de los siguientes filosofos, postula las ideas innatas en el sujeto", 255, 24, 676);
					texto("A) George Berkeley", 0, 36, 559);
					texto("B) David Hume", 0, 436, 559);
					texto("C) Leibniz", 0, 36, 595);
					texto("D) Hipatia", 0, 436, 595);
				}

				if (xash == 4) {
					if (al_key_down(&KeyState, ALLEGRO_KEY_A)) {
						al_set_timer_count(attack, 0);
						if (aux == 1) {
							hits1++;
							if (hits1 == 2 || hits1 == 4 || hits1 == 6 || hits1 == 8) {
								hpj2++;
							}
							resp = 1;
						}
						else {
							hits2++;
							if (hits2 == 2 || hits2 == 4 || hits2 == 6 || hits2 == 8) {
								hpj1++;
								life--;
							}
							resp = 2;
						}
						aux++;
						al_set_timer_count(wait, 0);
					}
					else if (al_key_down(&KeyState, ALLEGRO_KEY_B)) {
						al_set_timer_count(attack, 0);
						if (aux == 2 || aux == 4) {
							hits1++;
							if (hits1 == 2 || hits1 == 4 || hits1 == 6 || hits1 == 8) {
								hpj2++;
							}
							resp = 1;
						}
						else {
							hits2++;
							if (hits2 == 2 || hits2 == 4 || hits2 == 6 || hits2 == 8) {
								hpj1++;
								life--;
							}
							resp = 2;
						}
						al_set_timer_count(wait, 0);
						aux++;
					}
					else if (al_key_down(&KeyState, ALLEGRO_KEY_C)) {
						al_set_timer_count(attack, 0);
						if (aux == 3 || aux == 5 || aux == 6 || aux == 7 || aux == 8) {
							hits1++;
							if (hits1 == 2 || hits1 == 4 || hits1 == 6 || hits1 == 8) {
								hpj2++;
							}
							resp = 1;
						}
						else {
							hits2++;
							if (hits2 == 2 || hits2 == 4 || hits2 == 6 || hits2 == 8) {
								hpj1++;
								life--;
							}
							resp = 2;
						}
						al_set_timer_count(wait, 0);
						aux++;
					}
					else if (al_key_down(&KeyState, ALLEGRO_KEY_D)) {
						al_set_timer_count(attack, 0);
						resp = 2;
						al_set_timer_count(wait, 0);
						aux++;
						hits2++;
						if (hits2 == 2 || hits2 == 4 || hits2 == 6 || hits2 == 8) {
							hpj1++;
							life--;
						}
					};
				}
			}
			else if (resp == 1 && aux < 9) {
				if (hits1 == 2 || hits1 == 4 || hits1 == 6 || hits1 == 8) {
					texto("Los empiristas han contestado correctamente, Los racionalistas pierden 10 de vida", 255, 24, 676);
				}
				else {
					texto("Los empiristas han contestado correctamente, se acumulan 5 hitpoints", 255, 24, 676);
				}
				if (al_get_timer_count(attack) < 150) {
					if (xj1 < 480) {
						xj1 += 5;
					}
					if (yj1 > 110) {
						yj1 -= 2;
					}
					al_draw_tinted_bitmap_region(enemy, al_map_rgb(230, 0, 0), 200 * rnd1, 175.47 * rnd2, 200, 175.47, xj2, yj2, 0);
				}
				else {
					xj1 = 230;
					yj1 = 200;
					al_draw_tinted_bitmap_region(enemy, al_map_rgb(230, 0, 0), 200 * rnd1, 175.47 * rnd2, 200, 175.47, xj2, yj2, 0);
					if (al_get_timer_count(wait) == 180) {
						if (hpj2 == 4) {
							hpj2++;
						}
						resp = 0;
					}
				}
			}
			else if (resp == 2 && aux < 9) {
				if (hits2 == 2 || hits2 == 4 || hits2 == 6 || hits2 == 8) {
					texto("Los racionalistas han contestado correctamente, Los empiristas pierden 10 de vida", 255, 24, 676);
				}
				else {
					texto("Los racionalistas han contestado correctamente, se acumulan 5 hitpoints", 255, 24, 676);
				}
				if (al_get_timer_count(attack) < 150) {
					if (xj2 > 500) {
						xj2 -= 5;
					}
					if (yj2 < 200) {
						yj2 += 4.2;
					}
					al_draw_tinted_bitmap(ally, al_map_rgb(255, 0, 0), xj1, yj1, 0);
				}
				else {
					xj2 = 669;
					yj2 = 60;
					al_draw_tinted_bitmap(ally, al_map_rgb(255, 0, 0), xj1, yj1, 0);
					if (al_get_timer_count(wait) == 180) {
						if (hpj1 == 4) {
							hpj1++;
						}
						resp = 0;
					}
				}
			}
		}	
		if (first == 0) {
			if (al_get_timer_count(timer) >= 10) {
				if (xj2 > 669) {
					xj2 -= 10;
				}
				if (x2 < 110)
				{
					x2 += 10;
				}
				else
				{
					if (xash < 3) {
						xash++;
						if (xash == 1) {
							al_draw_bitmap_region(pokeball, 0 * 36, 0, 36, 36, 129, 436, NULL);
						}
						else if (xash == 2) {
							al_draw_bitmap_region(pokeball, 1 * 36, 0, 36, 36, 115, 396, NULL);
						}
						else if (xash == 3) {
							al_draw_bitmap_region(pokeball, 2 * 36, 0, 36, 36, 296, 396, NULL);
							x3 = 296;
						}
					}
					else
					{
						if (x3 < 400) {
							x3 += 13;
							if (al_get_timer_count(poketimer) == 10) {
								poke = 0;
							}
							else if (al_get_timer_count(poketimer) == 20) {
								poke = 1;
							}
							else if (al_get_timer_count(poketimer) == 30) {
								poke = 2;
							}
							else {
								poke = 3;
								al_set_timer_count(poketimer, 0);
							}
						}
						else {
							blast.blastdibujar = true;
							xash = 4;
							first = 1;
							poke = 4;
						}
					}
				}
				al_set_timer_count(timer, 0);
			}
		}
		cout << aux;
		al_flip_display();
	}
	return 1;
}

void batalla::texto(string _msg, int c, int _x, int _y) {
	al_draw_text(font, al_map_rgb(c, c, c), _x, _y, 0, _msg.c_str());
}

void batalla::reset() {
	xash = 0, poke = 5, x2 = 0, x3 = 0, resp = 0, xj2 = 768, hits1 = 0, hits2 = 0;
	aux = 1, yj2 = 60, xj1 = 230, yj1 = 200, first = 0, hpj1 = 0, hpj2 = 0;
}
