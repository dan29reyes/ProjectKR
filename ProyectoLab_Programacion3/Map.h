#pragma once
#include "Player.h"
#include <vector>
#include "Body.h"
#include "Npc.h"
#include "collider.h"

#ifndef MAP_H
#define MAP_H

class Map :public Body
{

	std::vector<collider>Colisions;

	std::vector<Npc> Npcs;


	Player* MainPlayer;
	bool load;
private:









public:


	Map(ALLEGRO_BITMAP* MapSprite, int _x, int _y, int _width, int _height, Player* _Player);
	Map();


	void AddColision(int ,int ,int,int);

	void AddNpc(ALLEGRO_BITMAP* _sprite, int _x, int _y, int _height, int _width,const char*Dialog);

	void movimiento();


	void LoadMap(bool);
	void DrawMap(int,int);
	Npc getNpcAt(int );


	





	



};



#endif // !MAP_H

