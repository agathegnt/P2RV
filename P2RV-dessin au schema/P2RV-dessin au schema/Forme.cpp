

#include "Forme.h"


int Forme::gettype(){
	return type;
}

Point Forme::getorigine(){
	return origine;
}
void Forme::setorigine(Point o){
	origine = o;
}
Point Forme::getextremite(){
	return extremite;
}
void Forme::setextremite(Point e){
	extremite = e;
}
Point Forme::getcentre(){
	return centre;
}
void Forme::setcentre(Point p){
	centre = p;
}