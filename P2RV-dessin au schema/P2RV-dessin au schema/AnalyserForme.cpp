#include "AnalyserForme.h"

<<<<<<< HEAD

//Fonction de distance entre deux points
=======
//=========== FONCTIONS UTILES ================================

>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
float distanceP(Point P1, Point P2, int W, int H) {
	return sqrt((P1.getx()*W/2 - P2.getx()*W/2)*(P1.getx()*W/2 - P2.getx()*W/2) + (P1.gety()*H/2 - P2.gety()*H/2)*(P1.gety()*H/2 - P2.gety()*H/2));
}

<<<<<<< HEAD

//retourne vrai si les deux segments passés en arguments sont presques perpendiculaires
=======
// retourne vrai si les segments sont perpendiculaires
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
bool IsPerpendicular (Segment f1, Segment f2)
{
	bool perpendicular = false;

    //calcul du produit scalaire
    Point vector1 = f1.getextremite()-f1.getorogine();
    Point vector2 = f2.getextremite()-f2.getorogine();
    int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

    if (prod_scal < 0,1)
    {
		perpendicular = true;
    }
	return perpendicular;
}

<<<<<<< HEAD
//retourne vrai si les deux segments passés en arguments sont presques parallèles
=======
// retourne vrai si les segments sont paralleles
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
bool IsParallel (Segment f1, Segment f2)
{
	//calcul du produit scalaire
	Point vector1 = f1.getextremite()-f1.getorogine();
	Point vector2 = f2.getextremite()-f2.getorogine();
	int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

	//compare le produit scalaire au produit des normes des vecteurs
	if (prod_scal - vector1.norme()*vector2.norme()< 0,1)
	{
		return true;
	}else{
		return false;
	}
}

//determine si la forme est fermee ou pas
bool IsClosed (Trait trait, int W, int distancemaxclosed)
{
	bool closed = false;
	vector<Point> table = trait.getTable();

	//le trait doit etre d'une taille superieure a 5
	if (table.size()>5)
	{
		Point vector = table[table.size()-1] - table[0];
		if (vector.norme()*W<=distancemaxclosed)//si les deux extrémités du trait sont proches, alors la forme est presque fermée
		{
			closed = true;
		}
	}
	return closed;
}

<<<<<<< HEAD

//détermine si un trait est presque un segment ou non
bool trouversegment(Trait trait, int distancemaxsegment, int W, int H) {
=======
//=========== ANALYSE SEGMENT ================================

bool trouversegment(Trait trait, float distancemax, int W, int H) {
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float AB = distanceP(nuage[0], nuage[j-1], W, H);
	int ABcarre = AB*AB;
	int AB2 = 2*AB;
	float BC;
	float AC;
	Point pointemp;
	for (int k = 0; k < j; k++){//pour chaque point du trait
		BC = distanceP(nuage[k], nuage[j-1], W, H);
		AC = distanceP(nuage[k], nuage[0], W, H);
		distot += sqrt(abs(AC*AC - ((ABcarre+AC*AC-BC*BC) / AB2) * ((ABcarre+AC*AC-BC*BC) / AB2)));//calcule la distance entre le point considéré et le segment reliant les extrémités du trait et l'ajoute à distot
	}
	if (distancemaxsegment*AB > distot) {//on accepte une erreur plus importante si le trait est plus long, d'ou la multiplication par AB
		return true;
	}
	else { return false; }
}

<<<<<<< HEAD
//détermine si un trait est presque un cercle ou non, et, si oui, met ce cercle dans le paramètre cercle
bool trouvercercle(Trait trait, Cercle& cercle, int distancemaxcercle, int W, int H) {
=======
//=========== ANALYSE CERCLE ================================

bool trouvercercle(Trait trait, Cercle& cercle, float distancemax, int W, int H) {
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float distmoy = 0.;
	Point centre=Point();
	for (int k = 0; k < j; k++){//on trouve le barycentre des points du trait ; il servira de centre
		centre.setx((nuage[k].getx() + k * centre.getx()) / (k + 1));
		centre.sety((nuage[k].gety() + k * centre.gety()) / (k + 1));
	}
	for (int k = 0; k < j; k++){//on calcule la distance moyenne entre le barycentre et les points du trait
		distmoy += distanceP(centre, nuage[k], W, H);
	}
	distmoy = distmoy/j;
	for (int k = 0; k < j; k++){//on calcule la somme des écarts à la distance moyenne
		distot += abs((distanceP(centre, nuage[k], W, H)-distmoy));
	}
	if (distancemaxcercle > distot) {//si cet écart est suffisamment petit, on a bien un cercle
		cercle.setcentre(centre);
		cercle.setrayon(distmoy*2/W);
		return true;
	}
	else { return false; }
}

<<<<<<< HEAD
//retourne l'indice coorespondant si le point existe dans le vector, -1 si non
int cherchevec(Point p, vector<Point> points){
	for (int i = 0; i < (signed)points.size(); i++)
	{
		if(p==points[i]){
			return i;
		}
	}
	return -1;
}

//cherche près de quels points importants de la liste de formes se trouve p, et le déplace au point le plus intéressant (si il existe); retourne true si déplace le point
bool ajoutpoint(Point* p, Point* bougepas, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	cout<<"analyse 1 extremite"<<endl;
	vector<Point> points;
	vector<int> indpoints;
	int j = 0;
	Point pointinterm;
	for (int i = 0; i < n-1; i++)
	{
		switch ((liste[i]->gettype()))
		{
		case SEGMENT:
			pointinterm = liste[i]->getextremite();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				cout<<"proche"<<endl;
				j = cherchevec(pointinterm, points);
				if(j>=0){
					indpoints[j]++;
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
			pointinterm = liste[i]->getorogine();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				cout<<"proche"<<endl;
				j = cherchevec(pointinterm, points);
				if(j>=0){
					indpoints[j]++;
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
		break;
		case CERCLE:
		case ARC:
			pointinterm = liste[i]->getcentre();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				cout<<"proche"<<endl;
				j = cherchevec(pointinterm, points);
				if(j>=0){
					indpoints[j]++;
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
		break;
		case TRAIT:
		break;
		default :

		break;
		}
	}
	if(points.size()==0){
		cout<<"RATEEEEEEEEEEEEEEEE"<<endl;
		return false;
	}else{
		int indice = 0;
		int val = 0;
		for (int i = 0; i < (signed)points.size(); i++)
		{
			if(indpoints[i]>val){
				val = indpoints[i];
				indice = i;
			}
		}
		cout<<"deplaceici"<<endl;
		pointinterm.setx(points[indice].getx());
		pointinterm.sety(points[indice].gety());
		cout<<liste[n-1]->getextremite().getx()<<endl;
		liste.pop_back();
		Segment* seg = new Segment();
		seg->setorogine(pointinterm);
		seg->setextremite(*bougepas);
		liste.push_back(seg);
		cout<<liste[n-1]->getextremite().getx()<<endl;
		return true;
	}
}

void AnalyseSegment(Segment* seg, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	bool originechangee = false;
	bool extremitechangee = false;

	//recherche de points
	
	originechangee = ajoutpoint(&(seg->getorogine()), &(seg->getextremite()), liste, n, distancemaxpoints, W, H);
	extremitechangee = ajoutpoint(&(seg->getextremite()), &(seg->getorogine()), liste, n, distancemaxpoints, W, H);

	//si pas de points trouvés, recherche de parallèles

	//si pas trouvés, recherche de perpendiculaire
}
=======
//=========== ANALYSE LIGNE BRISEE ================================

bool trouverlignebrisee(Trait trait, LigneBrisee& ligne, float distancemax, int W, int H) {
	//booleen retourne
	bool estLigne = false;

	//recuperation du nuage de points
	vector<Point> nuage = trait.getTable();
	int taille = nuage.size();

	int cpt = 1;
	int debut = 0;
	//initialisation du trait temporaire
	Trait trait_tmp = Trait();
	trait_tmp.ajout(nuage[debut]);

	//parcours de tous les points du trait
	while (cpt<taille)
	{
		//ajout du point suivant au trait temporaire
		trait_tmp.ajout(nuage[cpt]);

		//si avec ce point supplementaire on perd le segment
		if (!trouversegment(trait_tmp, distancemax, W, H))
		{
				//on cree un segment avec les points precedents
				Segment segment_tmp = Segment(nuage[debut], nuage[cpt-1]);
				//ajout de ce segment a la ligne BRISEE
				ligne.ajoutSegment(segment_tmp);
				//reinitialisation des donnees temporaires
				debut = cpt;
				trait_tmp = Trait();
				trait_tmp.ajout(nuage[debut]);
		}

		//incrementation du compteur
		cpt += 1;
	}

	if ((ligne.getTable()).size()>1)
	{
		estLigne = true;
	}
	return estLigne;
}
>>>>>>> bef21e61cbd4c95e74a4fb12c3d8cd4dda386c2c
