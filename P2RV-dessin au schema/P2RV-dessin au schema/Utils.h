#pragma once
#include <vector>
#include <math.h>
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Point
{
private:
	int x;
	int y;

public:
	//Constructeur
	Point();
	Point(int X, int Y);

	//Getters/Setters
	int getx();
	void setx(int X);
	int gety();
	void sety(int Y);
};

#ifndef M_PI
#define M_PI 3.141592
#endif 