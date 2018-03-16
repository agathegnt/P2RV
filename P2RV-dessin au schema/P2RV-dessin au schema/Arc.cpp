#include "Arc.h"

//Constructeur, avec centre, rayon, et deux valeurs d'angles en radians
Arc::Arc(Point c, float r, float o, float e){
	centre = c;
	rayon = r;
	if(o<e){
		angle1 = o;
		angle2 = e;
	}else{
		angle1 = e;
		angle2 = o;
	}
	afficher = true;
	type = ARC;
}

//Getters/setters
Point Arc::getcentre(){
	return centre;
}

//fonction pour tracer la Forme
void Arc::tracer(){
	float angle = angle1;
	for(int i=0; i<100; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		angle = angle+(angle2-angle1)/100;
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		glEnd();
	}
}