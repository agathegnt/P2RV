#pragma once

#include "Forme.h"

struct Arc : Forme
{
private:
	float rayon;
	float angle1;
	float angle2;

public:
	//Constructeur
	Arc(Point c, float r, float o, float e);

	//Getters/setters
	//virtual Point getcentre();

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef ARC
#define ARC 3
#endif