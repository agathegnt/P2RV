#include "Utils.h"

//Constructeurs
Point::Point(){
	x = 0;
	y = 0;
}
Point::Point(int X, int Y, int W, int H){
	x = (float)X/W*2-1;
	y = -(float)Y/H*2+1;
}

//Getters/Setters
float Point::getx(){
	return x;
}
void Point::setx(int X){
	x = X;
}
float Point::gety(){
	return y;
}
void Point::sety(int Y){
	y = Y;
}