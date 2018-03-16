#pragma once

#include "Utils.h"

class Forme
{
protected:
	int type;
public:
	Forme(){}
	int gettype();
	virtual void tracer(){}
	virtual void ajout(Point p){}
	virtual void setorogine(Point o){}
	virtual Point getorogine(){return Point();}
	virtual void setextremite(Point e){}
	virtual Point getextremite(){return Point();}
	virtual Point getcentre(){return Point();}
};





