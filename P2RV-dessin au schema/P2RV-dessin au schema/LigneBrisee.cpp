//=========== LIGNE BRISEE ================================

#include "LigneBrisee.h"

//Constructeur
LigneBrisee::LigneBrisee(){
	table = vector<Segment>(0);
	type = LIGNEBRISEE;
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
void LigneBrisee::tracer(){
	int taille = table.size();
	for (int i = 0; i < taille; i++)
	{
		table[i].tracer();
	}
}
