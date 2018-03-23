#pragma once

#include "Forme.h"

class Rectangle : public Forme
{
private:
	Point pointA;
	Point pointB;
	Point pointC;

public:
	//Constructeur
	Rectangle();
	Rectangle(Point A, Point B, Point C);

	//Setters
	void setA (Point A);
	void setB (Point B);
	void setC (Point C);


	//fonction pour tracer la Forme
	virtual void tracer();
};

#ifndef RECTANGLE
#define RECTANGLE 5
#endif
