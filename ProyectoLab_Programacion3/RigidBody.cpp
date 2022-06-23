#include "RigidBody.h"
#include <iostream>
RigidBody::RigidBody():Body(){}

RigidBody::RigidBody(ALLEGRO_BITMAP* _Sprite, int x, int y, int w,int h){
	Sprite = _Sprite;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
}

void RigidBody::movimiento(){}