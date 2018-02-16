#pragma once

#include "Utils.h"

struct Forme
{
private:

public:
	Forme(){}
	virtual void tracer(){}
	virtual void ajout(Point p){}
	virtual void setorogine(Point o){}
	virtual void setextremite(Point e){}
};

struct Segment : Forme
{
private:
	Point origine;
	Point extremite;

public:
	//Constructeur
	Segment();
	Segment(Point o, Point e);

	//Getters/Setters
	Point getorogine();
	virtual void setorogine(Point o);
	Point getextremite();
	virtual void setextremite(Point e);

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

	//Getters
	vector<Point> getTable ();

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
	Cercle();
	Cercle(Point p, float r);

	//getters/setters
	Point getcentre();
	void setcentre(Point o);
	float getrayon();
	void setrayon(float r);

	//fonction pour tracer la Forme
	virtual void tracer();
};
