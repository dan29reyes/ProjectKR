#pragma once
#include"Player.h"

class collider
{
private:

	Player* ColisionObj;

	int x;
	int y;
	int width;
	int height;

public :

	collider();



	collider(Player *,int,int,int,int);




	bool collide();


};

