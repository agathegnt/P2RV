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
	tracer(x, y);
}

void tracer(int x, int y, bool precedent, bool actuel) {
	if (precedent != actuel && precedent == false) {
		trait = new Trait();
		liste.push_back(trait);
		precedent = actuel;
	}
	trait.ajout(Point(x, y));
}

void vMouse(int button, int state, int x, int y)
{
	clicdroit(button,state,x,y)
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

// Le main vide pour le moment
int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);//taille initiale de fenetre, penser a modifier les 6 occurences de 600 dans deplacementSouris si change
	glutCreateWindow("Bras robot");
	W = 600.;
	H = 600.;

	// enregistrement des callbacks d'affichage
	// de redimensionnement et d'idle
	glutDisplayFunc(affichageScene);
	glutReshapeFunc(redimensionner);
	glutIdleFunc(affichageScene);

	// Declaration des callbacks souris
	glutMouseFunc(vMouse);
	glutMotionFunc(deplsouris);

	// Declaration des callbacks clavier
	glutKeyboardUpFunc(&clavier);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// enter GLUT event processing cycle
	glutMainLoop();


	return 1;
}