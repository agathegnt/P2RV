#include "Forme.h"

vector<Forme*> liste;//toutes les formes présentes
int n = 3;//le nombre de formes présentes


//taille fenetre
int W;
int H;

bool tracer = false;
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
	for (int i = 0; i < n; i++)
	{
		liste[i]->tracer();
	}

	// on echange les tampons d'affichage
	glutSwapBuffers();
	
}

void deplsouris(int x, int y) {
	if(tracer){
		cout<<"debut remplissage"<<endl;
		cout<<"n="<<n<<endl;
		liste[n-1]->ajout(Point(x, y, W, H));
	}
}

void vMouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			liste.push_back(new Trait());//=============================================faut un trait mais marche pas
			n++;
			tracer = true;
			cout<<tracer<<endl;
			//==================================================================liste[n]=new Trait(); //marche pas!!!
		} else {
			tracer = false;
		}
		break;
	default:
		printf("Erreur??\n");
		break;
	}
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

	liste.push_back(new Segment(Point(100, 100, W, H), Point(200, 200, W, H)));
	liste.push_back(new Cercle(Point(0, 0, W, H), 1.));
	liste.push_back(new Arc(Point(0, 0, W, H), 0.5, 0., 1.5));

	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}