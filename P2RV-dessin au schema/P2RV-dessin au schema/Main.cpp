#include "AnalyserForme.h"

vector<Forme*> liste;//toutes les formes présentes
int n = 0;//le nombre de formes présentes


//taille fenetre
int W;
int H;

int distancemaxclosed = 20;
int distancemaxclosedligne = 40;
int distancemaxcercle = 1000;
int distancemaxsegment = 2;
int distancepoint = 20;
int distanceminligne = 1;

bool tracer = false;
Trait* TraitaTester;
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
		liste[n-1]->ajout(Point(x, y, W, H));
	}
}

void vMouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			Trait* TraitenCours = new Trait();
			TraitaTester = TraitenCours;
			liste.push_back(TraitenCours);
			n++;
			tracer = true;
		} else {
			tracer = false;
			/*==========================================TESTS SUR liste[n]==========================
			if(est segment){
				for (int i = 0; i < liste.size(); i++)
				{
					proxi autres pts
					perp
					parallèle
				}
			}else{
				if(est fermé){
					if(cercle){
						proxi centre/autres pts
					}
				}else{
					if(arc){
						proxi centre autres pts
					}
				}
			}
			*/
			if(trouversegment(*TraitaTester, distancemaxsegment, W, H)){
				Point p1 = ((*TraitaTester).getTable())[0];
				Point p2 = ((*TraitaTester).getTable())[(((*TraitaTester).getTable()).size())-1];
				Segment* seg = new Segment();
				seg->setorogine(p1);
				seg->setextremite(p2);
				liste.pop_back();
				liste.push_back(seg);
				*seg = AnalyseSegment(seg, liste, n, distancepoint, W, H);
				liste.pop_back();
				liste.push_back(seg);
			}else{
				if(IsClosed (*TraitaTester, W, distancemaxclosed)){
					Cercle* cercle = new Cercle();
					if(trouvercercle(*TraitaTester, *cercle, distancemaxcercle, W, H)){
						liste.pop_back();
						liste.push_back(cercle);
					}
				}
				else
				{
					//test ligne brisee
					LigneBrisee* ligne = new LigneBrisee ();
					if (trouverlignebrisee(*TraitaTester, *ligne, distancemaxsegment, distanceminligne, W, H))
					{
						//ligne = LisseLigneBrisee(*ligne);
						liste.pop_back();
						liste.push_back(ligne);
						//test si polynome ou rectangle
						Rectangle* rectangle = new Rectangle();
						Polygone* polygone = new Polygone();
						if (trouverrectangle(*ligne, *rectangle, W, H, distancemaxclosedligne))
						{
							liste.pop_back();
							liste.push_back(rectangle);
						}
						else if (trouverpolygone(*ligne, *polygone, W, H, distancemaxclosedligne))
						{
							liste.pop_back();
							liste.push_back(polygone);
						}
					}
				}
			}
		}
		break;
	default:
		printf("Erreur??\n");
		break;
	}
}

void clavier(unsigned char key, int xx, int yy) {
	// Quelle touche a ete appuyee ?
	switch(key) {
	case 's' :
	case 'S' :
		if(n>0){
			liste.pop_back();
			n--;
		}
	break;
	// ESCAPE on termine l'application
	case 27 :
		exit(0);
    break;
   }
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(600,600);
	glutCreateWindow("Dessin");
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

	// Declaration des callbacks clavier
   glutKeyboardUpFunc(&clavier);

	/*liste.push_back(new Segment(Point(100, 100, W, H), Point(200, 200, W, H)));
	liste.push_back(new Cercle(Point(0, 0, W, H), 1.));
	liste.push_back(new Arc(Point(0, 0, W, H), 0.5, 0., 1.5));*/

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}