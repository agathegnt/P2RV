#include "Forme.h"

//===========SEGMENT===============================
//Constructeur
Segment::Segment(){
	origine = Point();
	extremite = Point();
}

Segment::Segment(Point o, Point e){
	origine = o;
	extremite = e;
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


//===========TRAIT================================
//Constructeur
Trait::Trait(){
	table = vector<Point>(0);
}

//Getters
vector<Point> Trait::getTable  ()
{
	return table;
}

//ajoute un point au vecteur de points
void Trait::ajout(Point p){
	table.push_back(p);
}

//fonction pour tracer la Forme
void Trait::tracer(){
	int taille = table.size();
	for (int i = 0; i < taille; i++)
	{
		glBegin(GL_POINTS);
			glColor3f(1., 1., 1.);
			glVertex2f(table[i].getx(), table[i].gety());
		glEnd();
	}

}


//===========ARC==================================
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
}

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


//===========CERCLE===============================
//Constructeur
Cercle::Cercle(){
	centre = Point();
	rayon = 0;
}

Cercle::Cercle(Point p, float r){
	centre = p;
	rayon = r;
}

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
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		angle = angle+2*M_PI/100;
	}
	glEnd();
}
