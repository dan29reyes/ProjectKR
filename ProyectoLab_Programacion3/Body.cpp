#include "Body.h"
#include <iostream>;

Body::Body(){
	x = 0;
	y = 0;
	Rx = 0;
	Ry = 0;
	speed = 0;
	Sprite = NULL;
	ColisionObj = NULL;
	width = 0;
	height = 0;
}

Body::Body(ALLEGRO_BITMAP* _Sprite, Player *_ColisionObj, int _width, int _height, int _x, int _y, int _speed, int _rx, int _ry) {
	reg = true;
	Sprite = _Sprite;
	ColisionObj = _ColisionObj;
	width = _width;
	height = _height;
	x = _x;
	y = _y;
	speed = _speed;
	Rx = _rx;
	Ry = _ry;
}

Body::Body(ALLEGRO_BITMAP*_Sprite, Player *_ColisionObj, int _width, int _height, int _x, int _y, int _speed){
	Sprite = _Sprite;
	ColisionObj = _ColisionObj;
	width = _width;
	height = _height;
	x = _x;
	y = _y;
	speed = _speed;
	reg = 0;
}

Body::Body(ALLEGRO_BITMAP*sprite, Player *_ColisionObj, int _x, int _y){
	speed = 1;
	width = al_get_bitmap_width(sprite);
	height = al_get_bitmap_height(Sprite);
	x = _x;
	y = _y;
	ColisionObj = _ColisionObj;
}

bool Body::collision(float x, float y, float ex, float ey, int width, int height){
	    if (x + width<ex || x>ex + width || y > ey + height || y + height < ey) {
			return false;
		}
		else {
			Body::Colision();
			//Colisiones de body
			return true;
		}
}






void Body::ClearBackGround(ALLEGRO_COLOR color)
{
	al_convert_mask_to_alpha(Sprite,color);
}

void Body::setX(int n)
{

	x = n;
}

void Body::setSpeed(int _speed)
{

	speed = _speed;

}

void Body::setY(int n)
{

	y = n;
}

int Body::getHeight()
{
	return height;
}

int Body::getWidth()
{
	return width;
}
void Body::setHeight(int _height)
{
	height = _height;
}

void Body::setWidth(int _width)
{

	width = _width;

}

int Body::getX()
{
	return x;
}

int Body::getY()
{
	return y;
}


void Body::Colision()
{
	if (ColisionObj->getDirY() == 3) {
		//Up
		ColisionObj->setY(ColisionObj->getY() + ColisionObj->getSpeed());
		std::cout << ColisionObj->getDirY() << "\n";




	}
	else if (ColisionObj->getDirY()==0) {
		//Down
		ColisionObj->setY(ColisionObj->getY() - ColisionObj->getSpeed());
		std::cout << ColisionObj->getDirY() << "\n";


	}
	else if (ColisionObj->getDirY()==1) {
		//Left
		ColisionObj->setX(ColisionObj->getX() + ColisionObj->getSpeed());

		std::cout << ColisionObj->getDirY() << "\n";



		


	
	
	}else if(ColisionObj->getDirY()==2) {
		//right
		ColisionObj->setX(ColisionObj->getX() - ColisionObj->getSpeed());
		
		std::cout << ColisionObj->getDirY()<<"\n";

		
	}

	
}











void Body::Draw(int Rx,int Ry)
{
	collision(ColisionObj->getX(), ColisionObj->getY(), x, y, width, height);

	if (Sprite != NULL) {
	
		al_draw_bitmap_region(Sprite, width * Rx, height * Ry, width, height, x, y, NULL);
	
	}
		
		
			
			


	



}

void Body::DrawScaled(int Rx, int Ry, int scale)
{
	al_draw_tinted_scaled_rotated_bitmap_region(Sprite,width*Rx , height *Ry, width, height,al_map_rgb(255,255,255),0,0,x ,y, scale, scale,0, 0);





}

