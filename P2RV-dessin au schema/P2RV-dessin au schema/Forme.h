#pragma once

#include "Utils.h"

struct Forme
{
private:

public:
	Forme(){}
	virtual void tracer(){}
	virtual void ajout(Point p){}
};

struct Segment : Forme
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

struct Trait : Forme
{
private:
	vector<Point> table;

public:
	//Constructeur
	Trait();

	vector<Point> gettable();

	//ajoute un poit au vecteur de points
	virtual void ajout(Point p);

	//fonction pour tracer la Forme
	virtual void tracer();
};

struct Arc : Forme
{
private:
	Point centre;
	float rayon;
	float angle1;
	float angle2;

public:
	//Constructeur
	Arc(Point c, float r, float o, float e);

	//fonction pour tracer la Forme
	virtual void tracer();
};

struct Cercle : Forme
{
private:
	Point centre;
	float rayon;

public:
	//Constructeur
	Cercle(Point p, float r);

	//fonction pour tracer la Forme
	virtual void tracer();
};