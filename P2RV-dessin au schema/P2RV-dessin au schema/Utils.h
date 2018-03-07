#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <cstdlib>
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Point
{
private:
	float x;
	float y;
	float z;

public:
	//Constructeur
	Point();
	Point(int X, int Y, int Z, int W, int H, int D);

	//Getters/Setters
	float getx();
	void setx(float X);
	float gety();
	void sety(float Y);
	float getz	();
	void setz(float Z);

	//fonction pour la norme d'un vecteur
	float norme();
	Point ProdVect(Point P1);

};
//surcharge
Point operator-(Point const& p1, Point const& p2);
Point operator+(Point const& p1, Point const& p2);
Point operator/(Point const& p1, float f);
Point operator*(float f, Point const& p1);

class Plan
{
private: 
	Point Attache;
	Point Normale;

public:
	//Constructeur
	Plan();
	Plan(Point Patt,Point Pnor);

	//Getters/Setters
	Point GetAttache();
	void SetAttache(Point Patt);
	Point GetNormale();
	void SetNormale();
}

#ifndef M_PI
#define M_PI 3.141592
#endif



