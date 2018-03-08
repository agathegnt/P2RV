#pragma once

#include "Forme.h"

struct Segment : Forme
{
private:

public:
	//Constructeur
	Segment();
	Segment(Point o, Point e);

	//Getters/Setters
	/*virtual Point getorigine();
	virtual void setorigine(Point o);
	virtual Point getextremite();
	virtual void setextremite(Point e);*/

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef SEGMENT
#define SEGMENT 1
#endif

//surcharge
bool operator==(Segment const& p1, Segment const& p2);