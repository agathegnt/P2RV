#include "AnalyserForme.h"

//toutes les formes presentes
vector<Forme*> liste;
//le nombre de formes presentes
int n = 0;

//taille fenetre
int W;
int H;

// ecarts mini et maxi
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

//fonction affichage
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

// fonction pour contruire un trait en fonction de deplacement souris
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
    // si le bonton droit est enfonce, trace d'un nouveau trait
		if (state == GLUT_DOWN)
    {
			TraitaTester = new Trait();
			liste.push_back(TraitaTester);
			n++;
			tracer = true;
		} else
      {
  			tracer = false;
        // initialisation des formes possibles
  			Segment* seg = new Segment();
  			LigneBrisee* ligne = new LigneBrisee ();
  			Cercle* cercle = new Cercle();

        // calcul des formes possibles et de l'erreur au trait d'origine
  			float errseg = trouversegment(*TraitaTester, W, H);
  			float errligne = trouverlignebrisee(*TraitaTester, *ligne, distanceminligne, distancemaxsegment, W, H);
  			float errcercle = 100;

        // mise a jour de l'erreur cercle si la forme est ferm�e (sinon, �a ne peut pas etre un cercle)
  			if(IsClosed (*TraitaTester, W, distancemaxclosed))
        {
  				errcercle = trouvercercle(*TraitaTester, *cercle, W, H);
  			}

        // si l'erreur segment est la plus faible
  			if(errseg <= errligne && errseg < errcercle)
			{
          //recuperation des donnees du trait
  				Point p1 = ((*TraitaTester).getTable())[0];
  				Point p2 = ((*TraitaTester).getTable())[(((*TraitaTester).getTable()).size())-1];
          //parametrage du segment
  				seg->setorigine(p1);
  				seg->setextremite(p2);
          //mise a jour du segment en fonction de l'environnement des formes existantes
  				*seg = AnalyseSegment(seg, liste, n, distancepoint, W, H);
          //ajout du segment a la liste de formes
  				liste.pop_back();
  				liste.push_back(seg);
        // si l'erreur ligne est la plus faible
  			} else if(errligne<errcercle)
			{
          //lissage et ajout de la ligne a la liste de formes
  				LisseLigneBrisee(*ligne, distancemaxclosed, W, H);
  				liste.pop_back();
  				liste.push_back(ligne);

          // analyse plus detaillee de la ligne brisee
  				Rectangle* rectangle = new Rectangle();
  				if (trouverrectangle(*ligne, *rectangle, W, H, distancemaxclosedligne))
  				{
  					liste.pop_back();
  					liste.push_back(rectangle);
  				}
  				Polygone* polygone = new Polygone();
  				if (trouverpolygone(*ligne, *polygone, W, H, distancemaxclosedligne))
  				{
  					liste.pop_back();
  					liste.push_back(polygone);
  				}
        // sinon si l'erreur la plus faible est celle du cercle
  			}else
        {
          //ajout du cercle a la liste de formes
  				liste.pop_back();
  				liste.push_back(cercle);
  			}
  					/*else{
  						trouver arc de cercle
  					}*/
		}
		break;
	  default:
		printf("Erreur??\n");
		break;
	}
}

// fonction parametrage des touches clavier
void clavier(unsigned char key, int xx, int yy) {
	// Quelle touche a ete appuyee ?
	switch(key) {
    //"s" supprime la derniere forme
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

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
