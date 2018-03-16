#include "Segment.h"

//Constructeur par défaut
Segment::Segment(){
	origine = Point();
	extremite = Point();
	afficher = true;
	type = SEGMENT;
}

//Constructeur, avec deux points
Segment::Segment(Point o, Point e){
	origine = o;
	extremite = e;
	afficher = true;
	type = SEGMENT;
}

//Getters/Setters
Point Segment::getorogine(){
	return origine;
}
void Segment::setorogine(Point o){
	origine = o;
}
Point Segment::getextremite(){
	return extremite;
}
void Segment::setextremite(Point e){
	extremite = e;
}

//fonction pour tracer la Forme
void Segment::tracer(){
	glBegin(GL_LINES);
		glColor3f(1., 0., 0.);
		glVertex2f(origine.getx(), origine.gety());
		glVertex2f(extremite.getx(), extremite.gety());
	glEnd();
}