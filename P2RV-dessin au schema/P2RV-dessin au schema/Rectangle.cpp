#include "Rectangle.h"

//Constructeur par défaut : rectangle nul
Rectangle::Rectangle(){
	pointA = Point();
	pointB = Point();
	pointC = Point();
	type = RECTANGLE;
}

//Constructeur, avec  les points
Rectangle::Rectangle(Point A, Point B, Point C){
	pointA = A;
	pointB = B;
	pointC = C;
	type = RECTANGLE;
}

//Setters
void Rectangle::setA (Point A)
{
	pointA = A;
}
void Rectangle::setB (Point B)
{
	pointB = B;
}
void Rectangle::setC (Point C)
{
	pointC = C;
}

//fonction pour tracer la Forme
void Rectangle::tracer(){
	//calcul du vecteur AB
	Point vectAB = Point();
	vectAB.setx(pointB.getx() - pointA.getx());
	vectAB.sety(pointB.gety() - pointA.gety());
	glBegin(GL_POLYGON);
		glColor3f(0., 0., 1.);
		// on trace les trois premiers points
		glVertex2f(pointA.getx(), pointA.gety());
		glVertex2f(pointB.getx(), pointB.gety());
		glVertex2f(pointC.getx(), pointC.gety());
		// dernier point = C - AB
		glVertex2f(pointC.getx()-vectAB.getx(), pointC.gety()-vectAB.gety());
	glEnd();
}
