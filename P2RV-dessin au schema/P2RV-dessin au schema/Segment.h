#pragma once

#include "Forme.h"

class Segment : public Forme
{
private:
	Point origine;
	Point extremite;

public:
	//Constructeur
	Segment();
	Segment(Point o, Point e);

	//Getters/Setters
	virtual Point getorogine();
	virtual void setorogine(Point o);
	virtual Point getextremite();
	virtual void setextremite(Point e);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef SEGMENT
#define SEGMENT 1
#endif