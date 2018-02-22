
<<<<<<< HEAD
#include "Forme.h"
using namespace std;
int Forme::gettype(){
	return type;
}
=======
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

//=========== LIGNE BRISEE ================================
//Constructeur
LigneBrisee::LigneBrisee(){
	table = vector<Segment>(0);
}

//Getters
vector<Segment> LigneBrisee::getTable  ()
{
	return table;
}

//ajoute un segment au vecteur de segments
void LigneBrisee::ajoutSegment(Segment s){
	table.push_back(s);
}

//fonction pour tracer la Forme
void Trait::tracer(){
	int taille = table.size();
	for (int i = 0; i < taille; i++)
	{
		table[i].tracer();
	}
}
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
