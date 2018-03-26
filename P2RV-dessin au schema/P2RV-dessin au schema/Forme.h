#pragma once

#include "Utils.h"

class Forme
{
protected:
	// le type est un entier correspondant a une geometrie particuliere
	int type;
public:
	//Constructeur
	Forme(){}

	//Getters
	int gettype();

	//Virtual fonctions
	virtual void tracer(){}
	virtual void ajout(Point p){}
	virtual void setorigine(Point o){}
	virtual Point getorigine(){return Point();}
	virtual void setextremite(Point e){}
	virtual Point getextremite(){return Point();}
	virtual Point getcentre(){return Point();}
};
