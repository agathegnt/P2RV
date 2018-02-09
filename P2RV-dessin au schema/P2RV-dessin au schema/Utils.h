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

public:
	//Constructeur
	Point();
	Point(int X, int Y, int W, int H);

	//Getters/Setters
	float getx();
	void setx(int X);
	float gety();
	void sety(int Y);

	//fonction pour la norme d'un vecteur
	double norme();

};
//surcharge
Point operator-(Point const& p1, Point const& p2);

#ifndef M_PI
#define M_PI 3.141592
#endif