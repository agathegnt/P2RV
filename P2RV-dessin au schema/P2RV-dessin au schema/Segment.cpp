#include "Segment.h"

//Constructeur par défaut
Segment::Segment(){
	origine = Point();
	extremite = Point();
	centre=Point();
	type = SEGMENT;
}

//Constructeur, avec deux points
Segment::Segment(Point o, Point e){
	origine = o;
	extremite = e;
	centre=Point();
	type = 1;
}

//Getters/Setters
/*Point Segment::getorigine(){
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
}*/

//fonction pour tracer la Forme
void Segment::tracer(){
	glBegin(GL_LINES);
		glColor3f(1., 0., 0.);
		glVertex2f(origine.getx(), origine.gety());
		glVertex2f(extremite.getx(), extremite.gety());
	glEnd();
}

//surcharge
bool operator==(Segment const& s1, Segment const& s2){
	// on copie les points pour ne pas les modifier
	Segment copie1 = s1;
	Segment copie2 = s2;

	return (copie1.getorigine()==copie2.getorigine() && copie1.getextremite()==copie2.getextremite());
}