#pragma once

#include "Utils.h"

class Forme
{
protected:
	int type;
	bool afficher;
public:
	Forme(){}
	int gettype();
	virtual void tracer(){}
	virtual void ajout(Point p){}
	virtual void setorigine(Point o){}
	virtual Point getorigine(){return Point();}
	virtual void setextremite(Point e){}
	virtual Point getextremite(){return Point();}
	virtual Point getcentre(){return Point();}
};





