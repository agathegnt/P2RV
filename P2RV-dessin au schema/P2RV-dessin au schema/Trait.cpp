#include "Trait.h"

//Constructeur
Trait::Trait(){
	table = vector<Point>(0);
	type = TRAIT;
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
