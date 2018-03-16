#pragma once

#include "Forme.h"

class Rectangle : public Forme
{
private:
	Point ref;
	Point oppose;

public:
	//Constructeur
	Rectangle();
	Rectangle(Point r, Point o);

	//Setters
	void setRef (Point r);
	void setOppose (Point o);

	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef RECTANGLE
#define RECTANGLE 5
#endif
