#include "Dialog.h"

ALLEGRO_FONT* Dialog::getFont(){
	return font;
}

Dialog::Dialog(const char*_dir, int size): StaticBody(0,0){
	dir = _dir;
	size = 23;
	load();
	curDialog = -1;
    font = al_load_font("fuente/pokemon_pixel_font.ttf",24,0);
}

std::vector<std::vector<std::string>>& Dialog::getMessages(){
	return MessageList;
}

void Dialog::load(){
	std::fstream File;
	File.open(dir, std::ios::in);//read
	std::string line;
	std::vector <std::string> Messages;
	while (File.is_open()) {
		if (std::getline(File, line)) {
			if (strcmp(line.c_str(), "END") == 0) {
				//Extrano gliythc con push bakc solo se pushe dos veces funciona
				addDiaog(Messages);
				Messages.clear();
			}
			else {
				std::cout << line << "END" << std::endl;
				Messages.push_back(line);
			}
		}
		else {
			File.close();
		}
	}
	std::cout << MessageList.size();
}

void Dialog::addDiaog(std::vector<std::string> vec){
	MessageList.push_back(vec);
}

Dialog::Dialog(){}

Dialog::~Dialog(){}
