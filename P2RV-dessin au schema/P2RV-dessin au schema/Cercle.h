#pragma once

#include "Forme.h"

class Cercle : public Forme
{
private:
	Point centre;
	float rayon;

public:
	//Constructeur
	Cercle();
	Cercle(Point p, float r);

	//getters/setters
	virtual Point getcentre();
	void setcentre(Point o);
	float getrayon();
	void setrayon(float r);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef CERCLE
#define CERCLE 2
#endif