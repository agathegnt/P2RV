#include "Cercle.h"

//Constructeur par defaut, cercle de rayon 0
Cercle::Cercle(){
	centre = Point();
	rayon = 0;
	type = CERCLE;
}

//Constructeur avec centre et rayon
Cercle::Cercle(Point p, float r){
	centre = p;
	rayon = r;
	type = CERCLE;
}

//Getters/Setters
Point Cercle::getcentre(){
	return centre;
}
void Cercle::setcentre(Point p){
	centre = p;
}
float Cercle::getrayon(){
	return rayon;
}
void Cercle::setrayon(float r){
	rayon = r;
}

//fonction pour tracer la Forme
void Cercle::tracer(){
	glBegin(GL_POLYGON);
	float angle = 0;
	for(int i=0; i<100; i++)
	{
		glColor3f(1., 1., 0.);
		glVertex2f(cos(angle)*rayon+centre.getx(), sin(angle)*rayon+centre.gety());
		angle = angle+2*M_PI/100;
	}
	glEnd();
}
