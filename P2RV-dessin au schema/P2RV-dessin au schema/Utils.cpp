#include "Utils.h"

//Constructeurs
Point::Point(){
	x = 0;
	y = 0;
}
Point::Point(int X, int Y){
	x = X;
	y = Y;
}

//Getters/Setters
int Point::getx(){
	return x;
}
void Point::setx(int X){
	x = X;
}
int Point::gety(){
	return y;
}
void Point::sety(int Y){
	y = Y;
}