#include "StaticBody.h"

StaticBody::StaticBody(int _x, int _y, int _width, int _height) {
	_x = x;
	_y = y;
	width = _width;
	height = _height;
}

StaticBody::StaticBody(){}

StaticBody::StaticBody(int _x, int _y) {
	x = _y;
	y = _y;
	height = 0;
	width = 0;
}
