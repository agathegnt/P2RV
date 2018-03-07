// Callback souris : but faire un callback souris voire plus


#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


//taille fenetre
float W;
float H;
bool precedent=false;
bool actuel = false;


void deplsouris(int x, int y) {
	tracer(x, y, precedent, actuel);
}

void tracer(int x, int y, bool precedent, bool actuel) {
	if (actuel && !precedent) {
		trait = new Trait();
		liste.push_back(trait);
		precedent = true;
	}
	trait.ajout(Point(x, y));
}

void vMouse(int button, int state, int x, int y)
{
	clicdroit(button,state,x,y);
}

void clicdroit(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		precedent = actuel;
		if (state == GLUT_DOWN && actuel == false) {
			actuel = true;
		}
		if (state == GLUT_UP && actuel == false) {
			actuel = true;
		}
		break;

	default:
		printf("Erreur??\n");
		break;
	}
}