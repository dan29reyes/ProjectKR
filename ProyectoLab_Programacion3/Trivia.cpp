#include "Trivia.h"

Trivia::Trivia(ALLEGRO_DISPLAY* display, Player* _Steve){
	ventana = display;
	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "Trivia");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);
	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 60);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(fps);
	Steve = _Steve;
}

int Trivia::politica(){
	life = Steve->getVida();
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("imagenes/politica.png");
	ALLEGRO_BITMAP** hearts = new ALLEGRO_BITMAP * [life];
	ALLEGRO_BITMAP* win = al_load_bitmap("imagenes/victoria.png");
	ALLEGRO_BITMAP* lost = al_load_bitmap("imagenes/derrota.png");
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_TIMER* limite = NULL;
	ALLEGRO_BITMAP* contador = al_load_bitmap("imagenes/counter.png");
	limite = al_create_timer(1.0);
	al_start_timer(limite);

	font = al_load_ttf_font("fuente/pokefuente.ttf", 40, ALLEGRO_ALIGN_CENTRE);
	timer = al_create_timer(1.0 / 60);
	al_start_timer(timer);
	al_draw_bitmap(Fondo, 0, 0, 0);

	for (int i = 0; i < life; i++) {
		hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
		al_draw_bitmap(hearts[i], i * 35, 0, 0);
	}

	while (true) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		ALLEGRO_KEYBOARD_STATE KeyState;
		ALLEGRO_EVENT event;
		al_get_keyboard_state(&KeyState);
		al_wait_for_event(event_queue, &event);
		if (life > 0) {
			if (aux != 6) {
				if (resp == 0) {
					segundos = al_get_timer_count(limite);
					al_draw_bitmap_region(contador, 91.11 * segundos, 0, 91.11, 150, 932.89, 0, 0);
					if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
						mousex = Evento.mouse.x;
						mousey = Evento.mouse.y;
						if (Evento.mouse.button & 1) {
							xp = 2;
							if (mousex >= 321 && mousex <= 376 && mousey >= 525 && mousey <= 795) {
								if (aux == 1) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 429 && mousex <= 481 && mousey >= 525 && mousey <= 795) {
								if (aux == 2 || aux == 3 || aux == 5) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 540 && mousex <= 592 && mousey >= 525 && mousey <= 795) {
								if (aux == 4) {
									resp = 1;
								}
								else {
									resp = 2;
									life--;
								}
								aux++;
							}
							else if (mousex >= 647 && mousex <= 703 && mousey >= 525 && mousey <= 795) {
								resp = 2;
								aux++;
								life--;
							}
						}
					}
					if (al_get_timer_count(limite) == 10) {
						life--;
						resp = 2;
						aux++;
					}
				}
				if (resp != 0) {
					if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
						al_clear_to_color(al_map_rgb(255, 255, 255));
						al_draw_bitmap(Fondo, 0, 0, 0);
						resp = 0;
						for (int i = 0; i < life; i++) {
							hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
							al_draw_bitmap(hearts[i], i * 35, 0, 0);
						}
						al_set_timer_count(limite, 0);
					};
				}
			}
			else {
				if (life > 0) {
					al_draw_bitmap(win, 0, 0, 0);
					Steve->setVida(life);
					Steve->setMedal(1);
					return 0;
				}
			}
		}
		else {
			al_draw_bitmap(lost, 0, 0, 0);
			Steve->setVida(life);
			return 0;
		}

		if (al_get_timer_count(timer) == 120) {
			al_set_timer_count(timer, 0);
		}
		al_flip_display();

		if (resp == 0) {
			texto("Seleccione el unknown con la respuesta correcta", 255, 206, 10);
			if (aux == 1) {
				texto("Durante el renacimiento, el modelo de", 255, 290, 380);
				texto("gobierno es uno de los siguientes :", 255, 310, 380 + 40);
				texto("A) Monarquia absoluta", 0, 120, 650);
				texto("B) Tirania republicana", 0, 570, 650);
				texto("C) Democracia participativa", 0, 120, 700);
				texto("D) Liberalismo politico", 0, 570, 700);
			}
			else if (aux == 2) {
				texto("De los siguientes acontecimientos, selecciones", 255, 222, 380);
				texto("el que inicia el periodo moderno:", 255, 320, 380 + 40);
				texto("A) Toma de Constantinopla", 0, 120, 650);
				texto("B) Tratado de paz de westfalia", 0, 560, 650);
				texto("C) Toma de la Bastilla", 0, 120, 700);
				texto("D) La ruta de la seda", 0, 560, 700);
			}
			else if (aux == 3) {
				texto("Durante el siglo XV, la sociedad se", 255, 290, 380);
				texto("estratifica en tres estamentos definidos :", 255, 248, 380 + 40);
				texto("A) Clase media, baja y alta", 0, 120, 650);
				texto("B) nobleza, clero y estado llano", 0, 540, 650);
				texto("C) Artesanos, guardianes y gobernantes", 0, 220, 700);
			}
			else if (aux == 4) {
				texto("Aparece el realismo politico, que se basaba", 255, 242, 380);
				texto("en un orden establecido, explicacion de un", 255, 242, 380 + 38);
				texto("sistema y recomendaciones", 255, 340, 380 + 76);
				texto("de como gobernar :", 255, 388, 380 + 114);
				texto("A) Tomas Moro", 0, 120, 650);
				texto("B) Jean Bodin", 0, 570, 650);
				texto("C) Nicolas Maquiavelo", 0, 120, 700);
				texto("D) Erasmo de Rotterdam", 0, 570, 700);
			}
			else if (aux == 5) {
				texto("Terminada la edad media, en el contexto", 255, 268, 380);
				texto("de la politica resulta que: ", 255, 361, 380 + 40);
				texto("A) La Iglesia resalta su poder", 0, 120, 635);
				texto("B) La Iglesia pierde el papel", 0, 520, 635);
				texto("   rector en la política", 0, 535, 635 + 36);
				texto("C) La Iglesia evangelica se", 0, 120, 635 + 40);
				texto("   posiciona en la politica", 0, 135, 635 + 76);
				texto("D) La politica desaparece", 0, 520, 635 + 72);
			}
		}
		else if (resp == 1) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(Fondo, 0, 0, 0);
			texto("Su respuesta es correcta", 0, 330, 667);
			texto("Presione espacio para continuar", 0, 299, 667 + 36);
		}
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(Fondo, 0, 0, 0);
			texto("Su respuesta es incorrecta", 0, 330, 667);
			texto("Presione espacio para continuar", 0, 299, 667 + 36);
		}
	}
}

void Trivia::reset(){
	 xr = 0, yr = 0, spins = 0, tipoS = 0;
	 spinning = false, running = true;
	 aux = 1;
	 resp = 0, xp = 0, mousex = 0, mousey = 0, segundos = 0;
}

int Trivia::historia() {
	life = Steve->getVida();
	font = al_load_ttf_font("fuente/pokefuente.ttf", 40, ALLEGRO_ALIGN_CENTRE);
	ALLEGRO_BITMAP* hist = al_load_bitmap("imagenes/historia.png");
	ALLEGRO_BITMAP* ans = al_load_bitmap("imagenes/hist.png");
	al_draw_bitmap(hist, 0, 0, 0);
	ALLEGRO_BITMAP** hearts = new ALLEGRO_BITMAP * [life];
	ALLEGRO_BITMAP* win = al_load_bitmap("imagenes/victoria.png");
	ALLEGRO_BITMAP* lost = al_load_bitmap("imagenes/derrota.png");
	ALLEGRO_TIMER* limite = NULL;
	ALLEGRO_BITMAP* contador = al_load_bitmap("imagenes/counter.png");
	limite = al_create_timer(1.0);
	al_start_timer(limite);

	for (int i = 0; i < life; i++) {
		hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
		al_draw_bitmap(hearts[i], i * 35, 0, 0);
	}

	while (true) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		ALLEGRO_KEYBOARD_STATE KeyState;
		ALLEGRO_EVENT event;
		al_get_keyboard_state(&KeyState);
		al_wait_for_event(event_queue, &event);

		if (life > 0) {
			if (aux != 6) {
				if (resp == 0) {
					segundos = al_get_timer_count(limite);
					al_draw_bitmap_region(contador, 91.11 * segundos, 0, 91.11, 150, 932.89, 618, 0);
					if (aux == 1) {
						texto("Uno de los siguientes personajes", 0, 48, 250);
						texto("fue el encargado de pintar la", 0, 68, 250 + 36);
						texto("capilla Sixtina :", 0, 150, 250 + 72);
						texto("A) La monarquia", 0, 665, 200);
						texto("B) El mercantilismo", 0, 665, 200 + 80);
						texto("D) La burguesia", 0, 665, 200 + 160);
						texto("C) El proletariado", 0, 665, 200 + 240);
						texto("Presione la letra correcta", 0, 600, 122);
						texto("para contestar", 0, 665, 150);
					}
					else if (aux == 2) {
						texto("El renacimiento supone una epoca de", 0, 38, 250);
						texto("absolutismo y nacionalismos, como el", 0, 38, 250 + 36);
						texto("el nacimiento de fuertes monarquias", 0, 38, 250 + 72);
						texto("europeas centralizadas como :", 0, 68, 250 + 108);
						texto("A) Grecia", 0, 665, 200);
						texto("B) Inglaterra", 0, 665, 200 + 80);
						texto("D) Yugoslavia", 0, 665, 200 + 160);
						texto("C) Egipto", 0, 665, 200 + 240);
						texto("Presione la letra correcta", 0, 600, 122);
						texto("para contestar", 0, 665, 150);
					}
					else if (aux == 3) {
						texto("Antes de la consolidacion del estado", 0, 38, 250);
						texto("moderno, Italia estuvo divida en ", 0, 58, 250 + 36);
						texto("pequenas ciudades - estado", 0, 78, 250 + 72);
						texto("normalmente enfrentadas entre si,", 0, 48, 250 + 108);
						texto("como es el caso de :", 0, 130, 250 + 144);
						texto("A) Florencia-Napoli", 0, 665, 200);
						texto("B) Amsterdam-Cracovia", 0, 665, 200 + 80);
						texto("D) Reims-Colonia", 0, 665, 200 + 160);
						texto("C) Milan-Lourdes", 0, 665, 200 + 240);
						texto("Presione la letra correcta", 0, 600, 122);
						texto("para contestar", 0, 665, 150);
					}
					else if (aux == 4) {
						texto("La toma de Constantinopla supone un", 0, 38, 250);
						texto("bloqueo comercial entre Europa y", 0, 48, 250 + 36);
						texto("Asia(la ruta de la seda) y ocurrio", 0, 48, 250 + 72);
						texto("en lo que hoy es actualmente :", 0, 76, 250 + 108);
						texto("A) Eslovaquia", 0, 665, 200);
						texto("B) Estambul en Turquia", 0, 665, 200 + 80);
						texto("D) Mesopotamia", 0, 665, 200 + 160);
						texto("C) Jerusalen", 0, 665, 200 + 240);
						texto("Presione la letra correcta", 0, 600, 122);
						texto("para contestar", 0, 665, 150);
					}
					else if (aux == 5) {
						texto("Resurge el interes por Grecia y Roma,", 0, 34, 250);
						texto("junto al declive del sistema feudal,", 0, 38, 250 + 36);
						texto("el crecimiento del comercio e", 0, 78, 250 + 72);
						texto("innovaciones entre las que", 0, 90, 250 + 108);
						texto("mencionamos: ", 0, 164, 250 + 144);
						texto("A) Grecia", 0, 665, 200);
						texto("B) Inglaterra", 0, 665, 200 + 80);
						texto("D) Yugoslavia", 0, 665, 200 + 160);
						texto("C) Egipto", 0, 665, 200 + 240);
						texto("Presione la letra correcta", 0, 600, 122);
						texto("para contestar", 0, 665, 150);
					}
					if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
						mousex = Evento.mouse.x;
						mousey = Evento.mouse.y;
						if (Evento.mouse.button & 1) {
							if (mousex >= 616 && mousex <= 920 && mousey >= 529 && mousey <= 580) {
								if (aux == 3 || aux == 5) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 701 && mousex <= 751 && mousey >= 531 && mousey <= 580) {
								if (aux == 2 || aux == 4) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 785 && mousex <= 835 && mousey >= 531 && mousey <= 580) {
								if (aux == 1) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 869 && mousex <= 920 && mousey >= 529 && mousey <= 580) {
								life--;
								resp = 2;
								aux++;
							}
						}
					}
					if (al_get_timer_count(limite) == 10) {
						life--;
						resp = 2;
						aux++;
					}
				}
				else if (resp == 1) {
					al_clear_to_color(al_map_rgb(255, 255, 255));
					al_draw_bitmap(ans, 0, 0, 0);
					for (int i = 0; i < life; i++) {
						hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
						al_draw_bitmap(hearts[i], i * 35, 0, 0);
					}
					texto("!!!Su respuesta es correcta!!!", 255, 309, 500);
					texto("Presione espacio para continuar", 255, 310, 611);
				}
				else {
					al_clear_to_color(al_map_rgb(255, 255, 255));
					al_draw_bitmap(ans, 0, 0, 0);
					for (int i = 0; i < life; i++) {
						hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
						al_draw_bitmap(hearts[i], i * 35, 0, 0);
					}
					texto("!!!Su respuesta es incorrecta!!!", 255, 307, 500);
					texto("Presione espacio para continuar", 255, 310, 611);
				}

				if (resp != 0) {
					if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
						al_clear_to_color(al_map_rgb(255, 255, 255));
						al_draw_bitmap(hist, 0, 0, 0);
						for (int i = 0; i < life; i++) {
							hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
							al_draw_bitmap(hearts[i], i * 35, 0, 0);
						}
						resp = 0;
						al_set_timer_count(limite, 0);
					};
				}
			}
			else {
				if (life > 0) {
					al_draw_bitmap(win, 0, 0, 0);
					Steve->setVida(life);
					Steve->setMedal(1);
					return 0;
				}
			}
		}
		else {
			al_draw_bitmap(lost, 0, 0, 0);
			Steve->setVida(life);
			Steve->setMedal(1);
			return 0;
		}

		al_flip_display();
	}
}

int Trivia::ciencia() {
	life = Steve->getVida();
	ALLEGRO_BITMAP* oak = al_load_bitmap("imagenes/Oak.png");
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("imagenes/ciencia.png");
	ALLEGRO_BITMAP* pokeball = al_load_bitmap("imagenes/pokeball.png");
	ALLEGRO_BITMAP** hearts = new ALLEGRO_BITMAP * [life];
	ALLEGRO_BITMAP* win = al_load_bitmap("imagenes/victoria.png");
	ALLEGRO_BITMAP* lost = al_load_bitmap("imagenes/derrota.png");
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* bueno = al_load_bitmap("imagenes/correcto.png");
	ALLEGRO_BITMAP* malo = al_load_bitmap("imagenes/incorrecto.png");
	ALLEGRO_TIMER* limite = NULL;
	ALLEGRO_BITMAP* contador = al_load_bitmap("imagenes/counter.png");

	font = al_load_ttf_font("fuente/pokefuente.ttf", 40, ALLEGRO_ALIGN_CENTRE);
	timer = al_create_timer(1.0);
	limite = al_create_timer(1.0);
	al_start_timer(timer);
	al_start_timer(limite);
	al_draw_bitmap(Fondo, 0, 0, 0);
	drawball(pokeball, xp, 160);
	drawball(pokeball, xp, 250);
	drawball(pokeball, xp, 340);
	drawball(pokeball, xp, 430);

	for (int i = 0; i < life; i++) {
		hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
		al_draw_bitmap(hearts[i], i * 35, 0, 0);
	}

	while (true) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		ALLEGRO_KEYBOARD_STATE KeyState;
		ALLEGRO_EVENT event;
		al_get_keyboard_state(&KeyState);
		al_wait_for_event(event_queue, &event);

		if (life > 0) {
			if (aux != 6) {
				if (resp == 0) {
					segundos = al_get_timer_count(limite);
					al_draw_bitmap_region(contador, 91.11 * segundos, 0, 91.11, 150, 932.89, 0, 0);
					if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
						mousex = Evento.mouse.x;
						mousey = Evento.mouse.y;
						if (Evento.mouse.button & 1) {
							xp = 2;
							if (mousex >= 160 && mousex <= 240 && mousey >= 445 && mousey <= 545) {
								life--;
								aux++;
								resp = 2;
							}
							else if (mousex >= 250 && mousex <= 330 && mousey >= 445 && mousey <= 545) {
								if (aux == 1 || aux == 3 || aux == 4 || aux == 5) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 340 && mousex <= 420 && mousey >= 445 && mousey <= 545) {
								if (aux == 2) {
									resp = 1;
								}
								else {
									resp = 2;
									life--;
								}
								aux++;
							}
							else if (mousex >= 430 && mousex <= 510 && mousey >= 445 && mousey <= 545) {
								resp = 2;
								aux++;
								life--;
							}
						}
					}
					if (al_get_timer_count(limite) == 10) {
						life--;
						resp = 2;
						aux++;
					}
				}
				if (resp != 0) {
					if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
						al_clear_to_color(al_map_rgb(255, 255, 255));
						al_draw_bitmap(Fondo, 0, 0, 0);
						drawball(pokeball, 0, 160);
						drawball(pokeball, 0, 250);
						drawball(pokeball, 0, 340);
						drawball(pokeball, 0, 430);
						for (int i = 0; i < life; i++) {
							hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
							al_draw_bitmap(hearts[i], i * 35, 0, 0);
						}
						resp = 0;
						al_set_timer_count(limite, 0);
					};
				}
			}
			else {
				if (life > 0) {
					al_draw_bitmap(win, 0, 0, 0);
					Steve->setVida(life);
					Steve->setMedal(1);
					return 0;
				}
			}
		}
		else {
			al_draw_bitmap(lost, 0, 0, 0);
			Steve->setVida(life);
			Steve->setMedal(1);
			return 0;
		}

		if (al_get_timer_count(timer) == 4) {
			al_set_timer_count(timer, 0);
		}
		al_flip_display();
		xo = (al_get_timer_count(timer) > 2) ? 0 : 1;

		if (resp == 0) {
			dibujaroak(oak, xo);
			if (aux == 1) {
				al_draw_filled_rectangle(136, 79, 900, 109 * 2, al_map_rgb(0, 0, 0));
				texto("Entre los siguientes renacentistas seleccione, uno de los", 255, 156, 94);
				texto("precursores filosofo-cientifico del heliocentrismo", 255, 156, 94 + 36);
				texto("(teoria que afirma que el sol es el centro del universo) : ", 255, 156, 94 + 72);
				texto("A) Tomas Moro", 0, 62, 624);
				texto("B) Galileo", 0, 512, 624);
				texto("C) Platon", 0, 62, 674);
				texto("D) Arquimedes", 0, 512, 674);
			}
			else if (aux == 2) {
				al_draw_filled_rectangle(136, 79, 900, 109 * 2, al_map_rgb(0, 0, 0));
				texto("El metodo cientifico se introduce por el interes de tres", 255, 156, 94);
				texto("filosofos. Entre los siguientes uno de los mencionados no", 255, 156, 94 + 36);
				texto("es precursor del metodo cientifico : ", 255, 156, 94 + 72);
				texto("A) Francis Bacon", 0, 62, 624);
				texto("B) Galileo Galilei", 0, 512, 624);
				texto("C) Nicolas Maquiavelo", 0, 62, 674);
				texto("D) René Descartes", 0, 512, 674);
			}
			else if (aux == 3) {
				al_draw_filled_rectangle(136, 79, 820, 140, al_map_rgb(0, 0, 0));
				texto("Es uno de los precursores del pensamiento Moderno: ", 255, 156, 94);
				texto("A) Isaac Newton", 0, 62, 624);
				texto("B) René Descartes", 0, 512, 624);
				texto("C) Erasmo de Roterdam", 0, 62, 674);
				texto("D) Francis Bacon", 0, 512, 674);
			}
			else if (aux == 4) {
				al_draw_filled_rectangle(136, 79, 900, 109 * 2, al_map_rgb(0, 0, 0));
				texto("De los siguientes filosofos niega el geocentrismo", 255, 156, 94);
				texto("(teoria que afirma que el centro de nuestro sistema", 255, 156, 94 + 36);
				texto("solar es la tierra) : ", 255, 156, 94 + 72);
				texto("A) Aristóteles", 0, 62, 624);
				texto("B) Nicolás Copérnico", 0, 512, 624);
				texto("C) Tomás de Aquino", 0, 62, 674);
				texto("D) Isaac Newton", 0, 512, 674);
			}
			else if (aux == 5) {
				al_draw_filled_rectangle(136, 79, 770, 180, al_map_rgb(0, 0, 0));
				texto("Uno de los inventos que suscito un conocimiento", 255, 156, 94);
				texto("ilimitado, fue el de Gutenberg : ", 255, 156, 94 + 36);
				texto("A) El astrolabio", 0, 62, 624);
				texto("B) La imprenta", 0, 512, 624);
				texto("C) La Nao y la Carabela", 0, 62, 674);
				texto("D) El Telescopio", 0, 512, 674);
			}
		}
		else if (resp == 1) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(bueno, 0, 0, 0);
		}
		else {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(malo, 0, 0, 0);
		}
	}
}

int Trivia::Ruleta(){
	al_start_timer(segundoTimer);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 21);
	int random = distr(gen);
	cout << random;

	font = al_load_ttf_font("fuente/pokefuente.ttf", 40, ALLEGRO_ALIGN_CENTRE);
	font2 = al_load_ttf_font("fuente/pokefuente.ttf", 60, ALLEGRO_ALIGN_CENTRE);
	ALLEGRO_BITMAP* fondo = al_load_bitmap("imagenes/sunset.png");
	ALLEGRO_BITMAP* tipoJ = al_load_bitmap("imagenes/TipoJuego.png");
	al_draw_bitmap(fondo, 0, 0, 0);
	ALLEGRO_BITMAP* rulet = al_load_bitmap("imagenes/ruleta.png");
	ALLEGRO_TIMER* rultime = NULL;

	rultime = al_create_timer(1.0 / 60);
	dibujaruleta(rulet, 0, 0);
	texto("Presione espacio para girar la ruleta", 255, 293, 660);

	while (true) {
		ALLEGRO_KEYBOARD_STATE KeyState;
		ALLEGRO_EVENT event;
		al_get_keyboard_state(&KeyState);
		al_wait_for_event(event_queue, &event);

		if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
			if (tipoS == 0) {
				al_start_timer(rultime);
				spinning = true;
			}
			else if (tipoS == 1) {
				ciencia();
			}
			else if (tipoS == 2) {
				arte();
			}
			else if (tipoS == 3) {
				historia();
			}
			else if (tipoS == 4) {
				politica();
			}
		};
		if (al_key_down(&KeyState, ALLEGRO_KEY_ESCAPE)) {
			return 0;
		}

		if (spins < random) {
			if (spinning == true) {
				if (al_get_timer_count(rultime) > 90) {
					xr = 0;
					yr = 0;
				}
				else if (al_get_timer_count(rultime) > 60) {
					xr = 1;
					yr = 0;
				}
				else if (al_get_timer_count(rultime) > 30) {
					xr = 0;
					yr = 1;
				}
				else if (al_get_timer_count(rultime) > 0) {
					xr = 1;
					yr = 1;
				}
				dibujaruleta(rulet, xr, yr);
			}
		}
		else if (spins == random) {
			if (random == 1 || random == 5 || random == 9 || random == 13 || random == 17 || random == 21) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_bitmap(tipoJ, 0, 0, 0);
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 66, 0, "El juego seleccionado es Ciencia");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 195, 122, 0, "Tiene 10 segundos para responder");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 600, 0, "Presione espacio para continuar");
				tipoS = 1;
				running = false;
			}
			else if (random == 2 || random == 6 || random == 10 || random == 14 || random == 18) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_bitmap(tipoJ, 0, 0, 0);
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 66, 0, "El juego seleccionado es Arte");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 195, 122, 0, "Tiene 10 segundos para responder");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 600, 0, "Presione espacio para continuar");
				tipoS = 2;
				running = false;
			}
			else if (random == 3 || random == 7 || random == 11 || random == 15 || random == 19) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_bitmap(tipoJ, 0, 0, 0);
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 66, 0, "El juego seleccionado es Historia");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 195, 122, 0, "Tiene 10 segundos para responder");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 600, 0, "Presione espacio para continuar");
				tipoS = 3;
				running = false;
			}
			else if (random == 4 || random == 8 || random == 12 || random == 16 || random == 20) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				al_draw_bitmap(tipoJ, 0, 0, 0);
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 66, 0, "El juego seleccionado es Politica");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 195, 122, 0, "Tiene 10 segundos para responder");
				al_draw_text(font2, al_map_rgb(255, 255, 255), 215, 600, 0, "Presione espacio para continuar");
				tipoS = 4;
				running = false;
			}
		}
		if (al_get_timer_count(rultime) == 120) {
			al_set_timer_count(rultime, 0);
			spins++;
		}
		else if (al_get_timer_count(rultime) == 90 || al_get_timer_count(rultime) == 60
			|| al_get_timer_count(rultime) == 30) {
			spins++;
		}
		al_flip_display();
	}
}

int Trivia::arte() {
	life = Steve->getVida();
	font = al_load_ttf_font("fuente/pokefuente.ttf", 40, ALLEGRO_ALIGN_CENTRE);
	ALLEGRO_BITMAP* gal = al_load_bitmap("imagenes/arte.png");
	al_draw_bitmap(gal, 0, 0, 0);
	ALLEGRO_BITMAP** hearts = new ALLEGRO_BITMAP*[life];
	ALLEGRO_BITMAP* win = al_load_bitmap("imagenes/victoria.png");
	ALLEGRO_BITMAP* lost = al_load_bitmap("imagenes/derrota.png");
	ALLEGRO_BITMAP* rotom = al_load_bitmap("imagenes/rotom.png");
	ALLEGRO_TIMER* limite = NULL;
	ALLEGRO_BITMAP* contador = al_load_bitmap("imagenes/counter.png");
	limite = al_create_timer(1.0);
	al_start_timer(limite);

	for (int i = 0; i < life; i++) {
		hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
		al_draw_bitmap(hearts[i], i * 35, 0, 0);
	}

	while (true) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		ALLEGRO_KEYBOARD_STATE KeyState;
		ALLEGRO_EVENT event;
		al_get_keyboard_state(&KeyState);
		al_wait_for_event(event_queue, &event);
		if (life > 0) {
			if (aux != 6) {
				if (resp == 0) {
					segundos = al_get_timer_count(limite);
					al_draw_bitmap_region(contador, 91.11 * segundos, 0, 91.11, 150, 932.89, 0, 0);
					if (aux == 1) {
						texto("Uno de los siguientes personajes fue el encargado", 255, 206, 174);
						texto("de pintar la capilla Sixtina :", 255, 336, 174 + 36);
						texto("Miguel", 0, 183, 379); texto("Angel", 0, 183, 379 + 36);
						texto("Donatello", 0, 356, 399);
						texto("Leonardo", 0, 553, 379); texto("Da Vinci", 0, 566, 379 + 36);
						texto("Francis", 0, 761, 379); texto("Bacon", 0, 770, 379 + 36);
						texto("Presione un boton de color para contestar", 255, 235, 611);
					}
					else if (aux == 2) {
						texto("Genio del renacimiento que esculpio el Moises, el David y la Pieta:", 255, 116, 204);
						texto("Miguel", 0, 183, 379); texto("Angel", 0, 183, 379 + 36);
						texto("Leonardo ", 0, 356, 379); texto("Da Vinci", 0, 370, 379 + 36);
						texto("Rafael", 0, 570, 379); texto("Sanzio", 0, 569, 379 + 36);
						texto("Galileo", 0, 765, 379); texto("Galilei", 0, 770, 379 + 36);
						texto("Presione un boton de color para contestar", 255, 235, 611);
					}
					else if (aux == 3) {
						texto("Durante el renacimiento el estilo artistico que impregno", 255, 126, 174);
						texto("el arte, la filosofia, la pintura escritura fue el :", 255, 126, 174 + 36);
						texto("Gotico", 0, 183, 400);
						texto("Barroco", 0, 365, 400);
						texto("Clasicismo", 0, 550, 400);
						texto("Romant", 0, 761, 379); texto("-icismo", 0, 770, 379 + 36);
						texto("Presione un boton de color para contestar", 255, 235, 611);
					}
					else if (aux == 4) {
						texto("Durante el renacimiento surge una nueva vision del", 255, 126, 174);
						texto("hombre, que se vio reflejada en el arte, en la politica", 255, 126, 174 + 36);
						texto("y en las ciencias sociales y humanas, a lo que se denomina :", 255, 126, 174 + 72);
						texto("Antropo", 0, 171, 379); texto("centrismo", 0, 157, 379 + 36);
						texto("Humanismo ", 0, 356, 400);
						texto("Paradigma", 0, 550, 370); texto("antropo", 0, 560, 370 + 36);
						texto("-logico", 0, 560, 370 + 72);
						texto("Galileo", 0, 765, 379); texto("Galilei", 0, 770, 379 + 36);
						texto("Presione un boton de color para contestar", 255, 235, 611);
					}
					else if (aux == 5) {
						texto("Cuatro genios del renacimiento (Leonardo, Donatello, Rafael y", 255, 126, 174);
						texto("Michelangelo) han sido llevados a la pantalla en los comics de :", 255, 126, 174 + 36);
						texto("Las", 0, 195, 370); texto("tortugas", 0, 161, 370 + 36); texto("ninjas", 0, 181, 370 + 72);
						texto("Los", 0, 395, 350); texto("caballeros", 0, 347, 350 + 36);
						texto("del", 0, 395, 350 + 72); texto("Zodiaco", 0, 368, 350 + 108);
						texto("Los", 0, 592, 350); texto("cuatro", 0, 570, 350 + 36);
						texto("fantas", 0, 570, 350 + 72); texto("ticos", 0, 580, 350 + 108);
						texto("antagon", 0, 759, 350); texto("-istas", 0, 764, 350 + 36);
						texto("Attack", 0, 763, 350 + 72); texto("Titan", 0, 769, 350 + 108);
						texto("Presione un boton de color para contestar", 255, 235, 611);
					}
					if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
						mousex = Evento.mouse.x;
						mousey = Evento.mouse.y;
						if (Evento.mouse.button & 1) {
							if (mousex >= 185 && mousex <= 250 && mousey >= 516 && mousey <= 540) {
								if (aux == 1 || aux == 2 || aux == 4) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if (mousex >= 379 && mousex <= 444 && mousey >= 515 && mousey <= 540) {
								if (aux == 3 || aux == 5) {
									resp = 1;
								}
								else {
									life--;
									resp = 2;
								}
								aux++;
							}
							else if ((mousex >= 575 && mousex <= 639 && mousey >= 515 && mousey <= 540) ||
								(mousex >= 774 && mousex <= 879 && mousey >= 515 && mousey <= 540)) {
								life--;
								aux++;
								resp = 2;
							}
						}
					}
					if (al_get_timer_count(limite) == 10) {
						life--;
						resp = 2;
						aux++;
					}
				}
				else if (resp == 1) {
					al_clear_to_color(al_map_rgb(255, 255, 255));
					al_draw_bitmap(gal, 0, 0, 0);
					al_draw_bitmap(rotom, 358, 124, 0);
					for (int i = 0; i < life; i++) {
						hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
						al_draw_bitmap(hearts[i], i * 35, 0, 0);
					}
					texto("!!!Su respuesta es correcta!!!", 255, 309, 172);
					texto("Presione espacio para continuar", 255, 310, 611);
				}
				else {
					al_clear_to_color(al_map_rgb(255, 255, 255));
					al_draw_bitmap(gal, 0, 0, 0);
					al_draw_bitmap(rotom, 358, 124, 0);
					for (int i = 0; i < life; i++) {
						hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
						al_draw_bitmap(hearts[i], i * 35, 0, 0);
					}
					texto("!!!Su respuesta es incorrecta!!!", 255, 307, 172);
					texto("Presione espacio para continuar", 255, 310, 611);
				}

				if (resp != 0) {
					if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
						al_clear_to_color(al_map_rgb(255, 255, 255));
						al_draw_bitmap(gal, 0, 0, 0);
						for (int i = 0; i < life; i++) {
							hearts[i] = al_load_bitmap("imagenes/pixelheart.png");
							al_draw_bitmap(hearts[i], i * 35, 0, 0);
						}
						resp = 0;
						al_set_timer_count(limite, 0);
					};
				}
			}
			else {
				if (life > 0) {
					al_draw_bitmap(win, 0, 0, 0);
					Steve->setVida(life);
					Steve->setMedal(1);
					return 0;
				}
			}
		}
		else {
			al_draw_bitmap(lost, 0, 0, 0);
			Steve->setVida(life);
			Steve->setMedal(1);
			return 0;
		}
		al_flip_display();
	}


}

void Trivia::dibujaroak(ALLEGRO_BITMAP* _sprite, int _x) {
	al_draw_bitmap_region(_sprite, 110 * _x, 256 * 0, 110, 256, 811, 297, 0);
}

void Trivia::drawball(ALLEGRO_BITMAP* _sprite, int _x, int _xpos) {
	al_draw_bitmap_region(_sprite, 80 * _x, 100 * 0, 80, 100, _xpos, 445, 0);
}

void Trivia::texto(string _msg, int c, int _x, int _y) {
	al_draw_text(font, al_map_rgb(c, c, c), _x, _y, 0, _msg.c_str());
}

void Trivia::dibujaruleta(ALLEGRO_BITMAP* _sprite, int _xr, int _yr) {
	al_draw_bitmap_region(_sprite, 300 * _xr, 300 * _yr, 300, 300, 365, 344, 0);
}