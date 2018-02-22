#include "Utils.h"

//Constructeurs
Point::Point(){
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(int X, int Y,int Z, int W, int H, int D){
	x = (float)X/W*2-1;
	y = -(float)Y/H*2+1;
	z= (float)Z/D*2-1
}

//Getters/Setters
float Point::getx(){
	return x;
}
void Point::setx(float X){
	x = X;
}
float Point::gety(){
	return y;
}
void Point::sety(float Y){
	y = Y;
}
float Point::getz() {
	return z;
}
void Point::setz(float Z) {
	y = Z;
}

//surcharge
Point operator-(Point const& p1, Point const& p2)
{
	// on copie les points pour ne pas les modifier
	Point copie1 = p1;
	Point copie2 = p2;

	Point resultat = Point();
	resultat.setx(copie1.getx()-copie2.getx());
	resultat.sety(copie1.gety()-copie2.gety());
	resultat.setz(copie1.getz() - copie2.getz());
	return resultat;
}

Point operator+(Point const& p1, Point const& p2)
{
	// on copie les points pour ne pas les modifier
	Point copie1 = p1;
	Point copie2 = p2;

	Point resultat = Point();
	resultat.setx(copie1.getx()+copie2.getx());
	resultat.sety(copie1.gety()+copie2.gety());
	resultat.setz(copie1.getz() + copie2.getz());
	return resultat;
}

Point operator/(Point const& p1, float f)
{
	// on copie les points pour ne pas les modifier
	Point copie1 = p1;

	Point resultat = Point();
	resultat.setx(copie1.getx()/f);
	resultat.sety(copie1.gety()/f);
	resultat.setz(copie1.getz() / f);
	return resultat;
}

Point operator*(float f, Point const& p1)
{
	// on copie les points pour ne pas les modifier
	Point copie1 = p1;

	Point resultat = Point();
	resultat.setx(f*copie1.getx());
	resultat.sety(f*copie1.gety());
	resultat.setz(f*copie1.getz());
	return resultat;
}

//fonction norme vecteur
float Point::norme()
{
	float norme = sqrt(x*x + y*y+z*z);
	return norme;
}
