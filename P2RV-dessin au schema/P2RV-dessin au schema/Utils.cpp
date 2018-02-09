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

//surcharge
Point operator-(Point const& p1, Point const& p2)
{
	// on copie les points pour ne pas les modifier
	Point copie1 = p1;
	Point copie2 = p2;

	Point resultat(copie1.getx()-copie2.getx(),copie1.gety()-copie2.gety());
	return resultat;
}
