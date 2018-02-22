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
	float const getx();
	void setx(float X);
	float const gety();
	void sety(float Y);

	//fonction pour la norme d'un vecteur
	float norme();

};
//surcharge
bool operator==(Point const& p1, Point const& p2);
Point operator-(Point const& p1, Point const& p2);
Point operator+(Point const& p1, Point const& p2);
Point operator/(Point const& p1, float f);
Point operator*(float f, Point const& p1);

#ifndef M_PI
#define M_PI 3.141592
#endif
