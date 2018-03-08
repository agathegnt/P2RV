#include "Rectangle.h"

//Constructeur rectangle nul
Rectangle::Rectangle(){
	ref = 0;
	oppose = 0;
	type = RECTANGLE;
}

//Constructeur, avec  les points
Rectangle::Rectangle(Point r, Point o){
	ref = r;
	oppose = o;
	type = RECTANGLE;
}

//Setters
void Rectangle::setRef (Point r)
{
	ref = r;
}
void Rectangle::setOppose (Point o)
{
	oppose = o;
}

//fonction pour tracer la Forme
void Rectangle::tracer(){
	glBegin(GL_POLYGON);
		glColor3f(1., 0., 0.);
		glVertex2f(ref.getx(), ref.gety());
		glVertex2f(oppose.getx(), ref.gety());
		glVertex2f(oppose.getx(), oppose.gety());
		glVertex2f(ref.getx(), oppose.gety());
	glEnd();
}
