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
Point Segment::getorigine(){
	return origine;
}
void Segment::setorigine(Point o){
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

bool operator==(Segment const& seg1, Segment const& seg2){
	// on copie les points pour ne pas les modifier
	Segment copie1 = seg1;
	Segment copie2 = seg2;

	return (copie1.getorigine()==copie2.getorigine() && copie1.getextremite()==copie2.getextremite());
}