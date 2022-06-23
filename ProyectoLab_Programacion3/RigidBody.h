#pragma once


#include"Body.h"
class RigidBody :public Body
{

private:





public:
	RigidBody();

	RigidBody(ALLEGRO_BITMAP* _Sprite,int x,int y,int w,int h);





	virtual void movimiento()  override;








};

