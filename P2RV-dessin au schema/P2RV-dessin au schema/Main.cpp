#include "Forme.h"

vector<Forme*> liste;//toutes les formes présentes
int n = liste.size();//le nombre de formes présentes

//taille fenetre
int W;
int H;

bool precedent=false;
bool actuel = false;

// Fonction de redimensionnement de la fenetre
void redimensionner(int w, int h) {
   
   // On evite une division par 0
   // la fenetre ne peut avoir une largeur de 0
   if (h == 0)
      h = 1;
   W=w*1.0;
   H=h*1.0;
   // Calcul du ratio
   float ratio =  (w * 1.0) / h;
   
   glViewport(0, 0, w, h);
   // on charge la matrice identite
   glLoadIdentity();
   
}

void affichageScene() {
   //On efface les tampons de couleur
   glClear(GL_COLOR_BUFFER_BIT);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
	//affichage principal
	int taille = liste.size();
	for (int i = 0; i < taille; i++)
	{
		liste[i]->tracer();
	}

	// on echange les tampons d'affichage
	glutSwapBuffers();
	
}

void tracer(int x, int y, bool precedent, bool actuel) {
	if (actuel && !precedent) {
		liste.push_back(new Forme());
		n++;
		//==================================================================liste[n]=new Trait(); marche pas!!!
		precedent = actuel;
	}
	liste[n]->ajout(Point(x, y));
}

void deplsouris(int x, int y) {
	tracer(x, y, precedent, actuel);
}

void clicdroit(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		precedent = actuel;
		if (state == GLUT_DOWN && !actuel) {
			actuel = true;
		}
		if (state == GLUT_UP && !actuel) {
			actuel = true;
		}
		break;

	default:
		printf("Erreur??\n");
		break;
	}
}

void vMouse(int button, int state, int x, int y)
{
	clicdroit(button,state,x,y);
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(600,600);
	glutCreateWindow("Bras robot");
	W=600;
	H=600;

	
	// enregistrement des callbacks d'affichage
	// de redimensionnement et d'idle
	glutDisplayFunc(affichageScene);
	glutReshapeFunc(redimensionner);
	glutIdleFunc(affichageScene);

	// Declaration des callbacks souris
	glutMouseFunc(vMouse);
	glutMotionFunc(deplsouris);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}