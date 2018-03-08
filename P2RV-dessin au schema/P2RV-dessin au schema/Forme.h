#pragma once

#include "Utils.h"

struct Forme
{
protected:
	int type;
	Point origine;
	Point extremite;
	Point centre;
public:
	Forme(){}
	int gettype();
	virtual void tracer(){}
	virtual void ajout(Point p){}
	void setorigine(Point o);
	Point getorigine();
	void setextremite(Point e);
	Point getextremite();
	Point getcentre();
	void setcentre(Point o);
};





