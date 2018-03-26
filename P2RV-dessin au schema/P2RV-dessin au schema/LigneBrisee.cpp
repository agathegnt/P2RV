//=========== LIGNE BRISEE ================================

#include "LigneBrisee.h"

//Constructeur par défaut : une ligne vide
LigneBrisee::LigneBrisee(){
	table = vector<Segment>(0);
	type = LIGNEBRISEE;
}

//Getters
vector<Segment> LigneBrisee::getTable  ()
{
	return table;
}

//Setters
void LigneBrisee::setpoint(bool ori, int indice, Point p){
	if(ori){
		table[indice].setorigine(p);
	}else{
		table[indice].setextremite(p);
	}
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
