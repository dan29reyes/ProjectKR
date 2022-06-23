#include "Map.h"

Map::Map(ALLEGRO_BITMAP*MapSprite, int _x, int _y, int _width, int _height , Player*_Player){
	MainPlayer = _Player;
	Sprite = MapSprite;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	load = false;
}

Map::Map(){
	x = 0;
	y = 0;
}

void Map::AddColision(int _x, int _y, int _width, int _height){
	Colisions.push_back(collider(MainPlayer, _x, _y, _width, _height));
}

void Map::AddNpc(ALLEGRO_BITMAP* _sprite, int _x, int _y, int _height, int _width,const char* Dialog){
	Npc c(_sprite, _x, _y, _height, _width,MainPlayer);
	c.LoadDialog(Dialog);
	Npcs.push_back(c);
}

void Map::movimiento() {}

void Map::LoadMap(bool _load){	
	load =_load;
}

void Map::DrawMap(int _Rx,int _Ry) {
	if (load) {
		al_draw_tinted_scaled_bitmap(Sprite, al_map_rgb(255, 255, 255), 0, 0, width, height, x, y, width * _Rx, height * _Ry,0);
		for (int i = 0; i < Colisions.size();i++) {
			Colisions.at(i).collide();
		}
		for (int i = 0; i < Npcs.size(); i++) {
			Npcs.at(i).Draw(0,0);
		}
	}
}

Npc Map::getNpcAt(int index) {
	return Npcs[index];
}