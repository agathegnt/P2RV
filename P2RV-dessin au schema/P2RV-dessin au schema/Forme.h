#pragma once

#include "Utils.h"

struct Forme
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
<<<<<<< HEAD
	virtual Point getextremite(){return Point();}
	virtual Point getcentre(){return Point();}
};
=======
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

//Une LigneBrisee est une succession de Segments
struct LigneBrisee : Forme
{
private:
	vector<Segment> table;

public:
	//Constructeur
	LigneBrisee();

	//Getters
	vector<Segment> getTable ();

	//ajoute un segment au vecteur de segments
	virtual void ajoutSegment(Segment s);

	//fonction pour tracer la Forme
	virtual void tracer();
};
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
