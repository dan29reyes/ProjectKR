#include "Player.h"
#include <iostream>

Player::Player() {
    dirX = 0;
    dirY = 0;
    vida = 7;
    medallas = 0;
}

Player::~Player() {
}

int Player::getVida() {
	return vida;
}

void Player::setVida(int _vida) {
    vida = _vida;
}

int Player::getMedal() {
	return medallas;
}

void Player::setMedal(int _medal) {
	medallas = _medal;
}

int Player::getTalkingPressed() {
    return TalkinPressed;
}

void Player::setTalking(bool isTalkin) {
    Talkin = isTalkin;
}

int Player::getHeight() {
    return height;
}

int Player::getDialogNum(){
    return dialogNum;
}

int Player::getWidth() {
    return width;
}

int Player::getY() {
    return y;
}

int Player::getDirY(){
    return dirY;
}

int Player::getSpeed(){
    return speed;
}

void Player::setX(int n){
    x = n;
}

void Player::setY(int n){
   y = n;
}

void Player::resetButtons(){
    TalkinPressed = 0;
}

void Player::resetDialogNum(){
    dialogNum = -1;
}

void Player::DrawMessageBox(int _x,int _y, const char*text,ALLEGRO_FONT* font){
    al_draw_scaled_bitmap(MessageBox, 0, 0, 600, 256, _x, _y, 600 * 1, 256 * 1, 0);
    /////////////////////////////////////////////////////////////////////
    al_draw_multiline_text(font, al_map_rgb(255, 255, 255), _x + 30, _y + 10,-10,20,0, text);
}

void Player::DrawMessageBox(int _x, int _y,std::vector<std::string> vector, ALLEGRO_FONT* font){
    al_draw_scaled_bitmap(MessageBox, 0, 0, 600, 256, _x, _y, 600 * 1, 256 * 1, 0);
    ////////////////////////////////////////////////////////////////////
    int Xpos = _x + 30, Ypos = _y + 10;
    for (int i = 0; i < vector.size();i++) {
        al_draw_text(font,al_map_rgb(255, 255, 255),Xpos,Ypos,0,vector[i].c_str());
        Ypos += 28;  
    }
}

bool Player::Talk(){
    Talkin = true;
    return true;
}

bool Player::isTalking(){
    return Talkin;
}

int Player::getX() {
    return x;
}

Player::Player(ALLEGRO_BITMAP* _Sprite) {
	Sprite = _Sprite;
    dirX = 0;
    dirY = 0;
    speed = 3;
    medallas = 0;
    x = 0;
    y = 0;
    vida = 8;
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();
    MessageBox = al_load_bitmap("Pokemon/MessageBox2.png");
    dialogNum = -1;
    Talkin = false;
}

void Player:: setWidht(int n) {
	width = n;
}

void Player::setHeight(int n) {
	height = n;
}

void Player::Mover(ALLEGRO_KEYBOARD_STATE KeyState, int *FrameRate) {
    bool anmation = false;
    int maxFrameRate = 4;
    if(!Talkin){
        if (al_key_down(&KeyState, ALLEGRO_KEY_W)) {
            y -= speed;
            dirY = 3;
            anmation = true;
        };
        if (al_key_down(&KeyState, ALLEGRO_KEY_S)) {
            y += speed;
            dirY = 0;
            anmation = true;
        }
        if (al_key_down(&KeyState, ALLEGRO_KEY_D) && (!al_key_down(&KeyState, ALLEGRO_KEY_W)) && (!al_key_down(&KeyState, ALLEGRO_KEY_S))) {
            x += speed;
            dirY = 2;
            anmation = true;
        }
        if (al_key_down(&KeyState, ALLEGRO_KEY_A) && (!al_key_down(&KeyState, ALLEGRO_KEY_W)) && (!al_key_down(&KeyState, ALLEGRO_KEY_S))) {
            x -= speed;
            dirY = 1;
            anmation = true;
        }
        
        if (dirX < 3) {
            if (anmation) {
                if (*FrameRate == maxFrameRate) {
                    dirX++;
                }
            }
        }
        else {
            dirX = 0;
            *FrameRate = 0;
        }
    }

    if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE) && TalkinPressed==0) {
        TalkinPressed = 1;
        dialogNum ++;
        std::cout << "Pressed:"<<dialogNum;
        //}
        if (!Talkin) {
           
            Talkin = true;
        }
        //else {
        //Talkin = false;
        anmation = true;
    }
    if (!al_key_down(&KeyState, ALLEGRO_KEY_SPACE)) {
        TalkinPressed = 0;
    }

    //Modificando frames con punteros
    if (*FrameRate > maxFrameRate) {
       *FrameRate = 0;
    }
    *FrameRate += 1;
}

void Player::Dibujar() {
	al_draw_bitmap_region(Sprite, width * dirX , height * dirY, width, height,x,y, NULL);
    if (Talkin) {
    }
}