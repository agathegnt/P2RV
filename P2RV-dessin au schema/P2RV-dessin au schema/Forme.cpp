#include "Forme.h"

//===========SEGMENT===============================
//Constructeur
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
			glColor3f(1., 0., 0.);
			glVertex2f(table[i].getx(), table[i].gety());
		glEnd();
	}
}


//===========ARC==================================
Arc::Arc(Point c, int r, Point o, Point e){
	centre = c;
	rayon = r;
	origine = o;
	extremite = e;
}

void Arc::tracer(){
	glBegin(GL_LINES);

	float lim1, lim2;
	if(origine.getx()>centre.getx()){
		lim1 = atan(abs(origine.gety()-centre.gety())/origine.getx()-centre.getx());
	}else{
		lim1 = M_PI/2 + atan(centre.getx()-origine.getx()/abs(centre.gety()-origine.gety()));
	}
	if(extremite.getx()>centre.getx()){
		lim2 = atan(abs(extremite.gety()-centre.gety())/extremite.getx()-centre.getx());
	}else{
		lim2 = M_PI/2 + atan(centre.getx()-extremite.getx()/abs(centre.gety()-extremite.gety()));
	}

	for(int i=0; i<100; i++)
	{
		float angle = 2*M_PI*i/100;
		if(lim1<angle && angle<lim2){
			glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		}
	}
	glEnd();
}


//===========CERCLE===============================
//Constructeur
Cercle::Cercle(Point p, int r){
	centre = p;
	rayon = r;
}

//fonction pour tracer la Forme
void Cercle::tracer(){
	glBegin(GL_POLYGON);
	for(int i=0; i<100; i++)
	{
		float angle = 2*M_PI*i/100;
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
	}
	glEnd();
}
