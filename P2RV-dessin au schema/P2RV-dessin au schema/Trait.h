#pragma once

#include "Forme.h"

// le trait est un vecteur rassemblant les points traces a la main
class Trait : public Forme
{
private:
	vector<Point> table;

public:
	//Constructeur
	Trait();

	//Getters
	vector<Point> getTable ();

	//fonction pour l'ajout d'un point au vecteur de points
	virtual void ajout(Point p);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef TRAIT
#define TRAIT 0
#endif
