#pragma once

#include "Segment.h"
#include "Trait.h"

//Une LigneBrisee est une succession de Segments
struct LigneBrisee : Forme
{
private:
	vector<Segment> table;

public:
	//Constructeur
	LigneBrisee();

	//Getters
	vector<Segment> getTable ();

	//ajoute un segment au vecteur de segments
	virtual void ajoutSegment(Segment s);

	//fonction pour tracer la Forme
	virtual void tracer();
