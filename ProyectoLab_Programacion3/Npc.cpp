#include "Npc.h"

Npc::Npc(ALLEGRO_BITMAP* _sprite, int _x, int _y, int _width, int _height,Player* _p){
	width = _width;
	height = _height;
	x = _x;
	y = _y;
	Sprite = _sprite;
	ColisionObj = _p;
	collider col(_p,_x,_y,_width,_height);
	Sign = al_load_bitmap("imagenes/Interrogation.png");
}

bool Npc::inRange() {
	if (ColisionObj->getX() + width+20<x  || ColisionObj->getX()>x + width + 20 || ColisionObj->getY() > y + height + 20 || ColisionObj->getY() +height + 20 <y) {
		return false;
	}
	//si em vas d ibujar el texto qeu seea en esta posicion
	if (ColisionObj->getDialogNum() >= 0 && ColisionObj->getDialogNum() < Npc_Dialog.getMessages().size()) {
		int num = ColisionObj->getDialogNum();
		ColisionObj->DrawMessageBox(ColisionObj->getX()-300,ColisionObj->getY()+100, Npc_Dialog.getMessages().at(num), Npc_Dialog.getFont());
	}
	else {
		ColisionObj->resetDialogNum();
		ColisionObj->setTalking(false);
	}
	return true;
}

void Npc::Draw(int Rx,int Ry) {
	Body::Draw(Rx, Ry);
	if (ColisionObj != NULL) {
		if (Sprite != NULL) {
			collision(ColisionObj->getX(), ColisionObj->getY(), x, y, width, height);
			al_draw_bitmap_region(Sprite, width * Rx, height * Ry, width, height, x, y, 0);
		}
		
		if (inRange()) {
			al_draw_bitmap(Sign, x, y - 20, 0);
		}
	}
}

void Npc::LoadDialog(const char*text){
	 Npc_Dialog = Dialog(text, 32);
}

void Npc::movimiento() {}