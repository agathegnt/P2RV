#pragma once

#include "Forme.h"

//structure polygone regulier
class Polygone : public Forme
{
private:
	Point premier;
	Point direction;
	int sommets;

public:
	//Constructeur
	Polygone();

	//Setters
	void setPremier (Point p);
	void setDirection (Point d);
	void setSommets (int s);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef POLYGONE
#define POLYGONE 6
#endif
