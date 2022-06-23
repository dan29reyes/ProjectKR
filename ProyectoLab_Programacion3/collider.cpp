#include "collider.h"
#include<iostream>

collider::collider(){}

collider::collider(Player*p, int _x, int _y, int _width, int _height){
	ColisionObj = p;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

bool collider::collide(){
    //(ColisionObj->getX() >= x && ColisionObj->getX() <= width) && (ColisionObj->getY() >= y && ColisionObj->getY() <= height)
	if (ColisionObj->getX() + width<x || ColisionObj->getX()>x + width || ColisionObj->getY() > y + height || ColisionObj->getY() + height < y) {
		return false;
	}else {
        std::cout << "collision detected\n";
        if (ColisionObj->getDirY() == 3) {
            //Up            
            ColisionObj->setY(ColisionObj->getY() + ColisionObj->getSpeed());
        }
        else if (ColisionObj->getDirY() == 0) {
            //Down
            ColisionObj->setY(ColisionObj->getY() - ColisionObj->getSpeed());
        }
        else if (ColisionObj->getDirY() == 1) {
            //Left
            ColisionObj->setX(ColisionObj->getX() + ColisionObj->getSpeed());
        }
        else if (ColisionObj->getDirY() == 2) {
            //right
            ColisionObj->setX(ColisionObj->getX() - ColisionObj->getSpeed());
        }
    }
	return true;
}