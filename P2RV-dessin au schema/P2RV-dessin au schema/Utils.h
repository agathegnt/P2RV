#pragma once
#include <iostream>
#include <cstdlib>
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
};

#ifndef M_PI
#define M_PI 3.141592
#endif 