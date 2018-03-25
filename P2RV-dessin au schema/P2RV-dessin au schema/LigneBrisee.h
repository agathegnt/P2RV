#pragma once

#include "Segment.h"
#include "Trait.h"

//Une LigneBrisee est une succession de Segments
class LigneBrisee : public Forme
{
private:
	vector<Segment> table;

public:
	//Constructeur
	LigneBrisee();

	//Getters
	vector<Segment> getTable ();

	//Setters
	void setpoint(bool ori, int indice, Point p);

	//fonction qui ajoute un segment au vecteur de segments
	virtual void ajoutSegment(Segment s);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef LIGNEBRISEE
#define LIGNEBRISEE 4
#endif
