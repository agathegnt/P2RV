#pragma once

#include "Forme.h"

{
private:
	vector<Point> table;

public:
	//Constructeur
	Trait();

	//Getters
	vector<Point> getTable ();

	//ajoute un poit au vecteur de points
	virtual void ajout(Point p);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef TRAIT
#define TRAIT 0
#endif