#pragma once

#include "Utils.h"

class Forme
{
private:

public:
	Forme(){}
	virtual void tracer(){}
	virtual void ajout(Point p){}
};

class Segment : Forme
{
private:
	Point origine;
	Point extremite;

public:
	//Constructeur
	Segment(Point o, Point e);

	//Getters/Setters
	Point getorogine();
	void setorogine(Point o);
	Point getextremite();
	void setextremite(Point e);

	//fonction pour tracer la Forme
	virtual void tracer();
};

class Trait : Forme
{
private:
	vector<Point> table;

public:
	//Constructeur
	Trait();

	//ajoute un poit au vecteur de points
	virtual void ajout(Point p);

	//fonction pour tracer la Forme
	virtual void tracer();
};

class Arc : Forme
{
private:
	Point centre;
	int rayon;
	Point origine;
	Point extremite;

public:
	//Constructeur
	Arc(Point c, int r, Point o, Point e);

	//fonction pour tracer la Forme
	virtual void tracer();
};

class Cercle : Forme
{
private:
	Point centre;
	int rayon;

public:
	//Constructeur
	Cercle(Point p, int r);

	//fonction pour tracer la Forme
	virtual void tracer();
};