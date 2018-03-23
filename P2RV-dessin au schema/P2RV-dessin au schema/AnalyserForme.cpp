#include "AnalyserForme.h"


//=========== FONCTIONS UTILES ================================

//Fonction de distance entre deux points
float distanceP(Point P1, Point P2, int W, int H) {
	return sqrt((P1.getx()*W/2 - P2.getx()*W/2)*(P1.getx()*W/2 - P2.getx()*W/2) + (P1.gety()*H/2 - P2.gety()*H/2)*(P1.gety()*H/2 - P2.gety()*H/2));
}


//retourne vrai si les deux segments pass�s en arguments sont presques perpendiculaires
bool IsPerpendicular (Forme f1, Segment f2)
{
	bool perpendicular = false;

    //calcul du produit scalaire
    Point vector1 = f1.getextremite()-f1.getorogine();
    Point vector2 = f2.getextremite()-f2.getorogine();
    int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

    if (prod_scal < 0.08)
    {
		perpendicular = true;
    }
	return perpendicular;
}


//retourne vrai si les deux segments pass�s en arguments sont presques parall�les
bool IsParallel (Forme f1, Segment f2)
{
	//calcul du produit scalaire
	Point vector1 = f1.getextremite()-f1.getorogine();
	Point vector2 = f2.getextremite()-f2.getorogine();
	int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

	//compare le produit scalaire au produit des normes des vecteurs
	if (prod_scal - vector1.norme()*vector2.norme()< 0.08)
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
		if (vector.norme()*W<=distancemaxclosed)//si les deux extr�mit�s du trait sont proches, alors la forme est presque ferm�e
		{
			closed = true;
		}
	}
	return closed;
}

//determine si la ligne brisee est fermee ou pas
bool IsClosedLigne (LigneBrisee ligne, int W, int distancemaxclosed)
{
	bool closed = false;
	vector<Segment> table = ligne.getTable();
	Point debut = table[0].getorigine();
	Point fin = table[table.size()-1].getextremite();
	Point vector = fin - debut;
	//si les deux extremites du trait sont proches, alors la forme est presque fermee
	if (vector.norme()*W<=distancemaxclosed)
	{
		closed = true;
	}
	return closed;
}

//=========== ANALYSE SEGMENT ================================

//determine si un trait est presque un segment ou non
bool trouversegment(Trait trait, int distancemaxsegment, int W, int H) {
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
		distot += sqrt(abs(AC*AC - ((ABcarre+AC*AC-BC*BC) / AB2) * ((ABcarre+AC*AC-BC*BC) / AB2)));//calcule la distance entre le point consid�r� et le segment reliant les extr�mit�s du trait et l'ajoute � distot
	}
	if (distancemaxsegment*AB > distot) {//on accepte une erreur plus importante si le trait est plus long, d'ou la multiplication par AB
		return true;
	}
	else { return false; }
}

//=========== ANALYSE CERCLE ================================

//determine si un trait est presque un cercle ou non, et, si oui, met ce cercle dans le parametre cercle
bool trouvercercle(Trait trait, Cercle& cercle, int distancemaxcercle, int W, int H) {
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
	for (int k = 0; k < j; k++){//on calcule la somme des �carts � la distance moyenne
		distot += abs((distanceP(centre, nuage[k], W, H)-distmoy));
	}
	if (distancemaxcercle > distot) {//si cet �cart est suffisamment petit, on a bien un cercle
		cercle.setcentre(centre);
		cercle.setrayon(distmoy*2/W);
		return true;
	}
	else { return false; }
}


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

//cherche pres de quels points importants de la liste de formes se trouve p, et retourne le point le plus interessant (si il existe)
Point ajoutpointconfondu(Point* p, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
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
		return Point(1000, 1000, W, H);
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
		pointinterm.setx(points[indice].getx());
		pointinterm.sety(points[indice].gety());
		cout<<liste[n-1]->getextremite().getx()<<endl;
		return pointinterm;
	}
}

Point ajoutperpendicularite(Segment seg, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	Point pointinterm;
	vector<Point> points;
	vector<int> indpoints;
	int j = 0;
	for (int i = 0; i < n-1; i++)
	{
		if(liste[i]->gettype()==SEGMENT){
			if(IsPerpendicular (*liste[i], seg)){
				j = cherchevec(pointinterm, points);
				if(j>=0){
					indpoints[j]++;
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
		}
	}
	if(points.size()==0){
		return Point(1000, 1000, W, H);
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

	}
	return pointinterm;
}

Segment AnalyseSegment(Segment* seg, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	Point origine = seg->getorogine();
	Point extremite = seg->getextremite();
	bool or = false;
	bool ex = false;
	Segment newseg;
	newseg.setorogine(origine);
	newseg.setextremite(extremite);
	//recherche de points

	origine = ajoutpointconfondu(&(seg->getorogine()), liste, n, distancemaxpoints, W, H);
	if(origine.getx()<1){
		or = true;
		newseg.setorogine(origine);
	}

	extremite = ajoutpointconfondu(&(seg->getextremite()), liste, n, distancemaxpoints, W, H);
	if(extremite.getx()<1){
		ex = true;
		newseg.setextremite(extremite);
	}

	//si pas trouves, recherche de perpendiculaire
	if(!or){
		origine = ajoutperpendicularite(*seg, liste, n, distancemaxpoints, W, H);
		if(origine.getx()<1){
			or = true;
			newseg.setorogine(origine);
		}
	}
	if(!ex){
		extremite = ajoutperpendicularite(*seg, liste, n, distancemaxpoints, W, H);
		if(extremite.getx()<1){
			ex = true;
			newseg.setextremite(extremite);
		}
	}
	//si pas de points trouves, recherche de paralleles



	return newseg;
}


//=========== ANALYSE LIGNE BRISEE ================================

bool trouverlignebrisee(Trait trait, LigneBrisee& ligne, int distancemax, int distanceminligne, int W, int H) {
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
				//ajout de ce segment a la ligne BRISEE ssi il est suffisemment long
				if (distanceP(nuage[debut],nuage[cpt-1],W,H)  > distanceminligne)
				{
					ligne.ajoutSegment(segment_tmp);
					estLigne = true;
				}
				//reinitialisation des donnees temporaires
				debut = cpt;
				trait_tmp = Trait();
				trait_tmp.ajout(nuage[debut]);
		}
		else if (cpt == (taille-1))
		{
			//on cree un segment avec les derniers points
			Segment segment_tmp = Segment(nuage[debut], nuage[cpt]);
				//ajout de ce segment a la ligne BRISEE ssi il est suffisemment long
				if (distanceP(nuage[debut],nuage[cpt],W,H)  > distanceminligne)
				{
					ligne.ajoutSegment(segment_tmp);
					estLigne = true;
				}
		}
		//incrementation du compteur
		cpt += 1;
	}
	return estLigne;
}

LigneBrisee* LisseLigneBrisee(LigneBrisee ligne){
	LigneBrisee *newligne = new LigneBrisee();
	int taille = (ligne.getTable()).size();
	newligne->ajoutSegment(Segment());
	(newligne->getTable()[0]).setorigine((ligne.getTable()[0]).getorigine());
	for (int i = 0; i < taille-1; i++)
	{
		newligne->ajoutSegment(Segment());
		Point *p = new Point();
		Point *p1 = new Point();
		Point *p2 = new Point();
		*p1=ligne.getTable()[i].getextremite();
		*p2=ligne.getTable()[i+1].getorigine();
		*p=(*p1+*p2)/2;
		newligne->getTable()[i].setextremite(*p);
		newligne->getTable()[i+1].setorogine(*p);
	}
	(newligne->getTable()[taille-1]).setextremite((ligne.getTable()[taille-1]).getextremite());
	return newligne;
}

//=========== ANALYSE RECTANGLE ================================

bool trouverrectangle (LigneBrisee ligne, Rectangle& rectangle, int W, int H, int distancemaxclosed){
	//booleen retourne
	bool est_rectangle = false;
	//table des segments
	vector<Segment> segmentTable = ligne.getTable();

	if (segmentTable.size()==4)
	{
		// si la forme est fermee
		if (IsClosedLigne(ligne,W,distancemaxclosed))
		{
			//si les segments opposes sont paralleles
			if (IsParallel (segmentTable[0], segmentTable[2]) && IsParallel (segmentTable[1], segmentTable[3]))
			{
				//et si les deux premiers segments sont perprendiculaires
				if (IsPerpendicular (segmentTable[0], segmentTable[1]))
				{
					est_rectangle = true;
					//parametrage du point A
					rectangle.setA(segmentTable[0].getorigine());
					//parametrage du point B
					rectangle.setB(segmentTable[1].getorigine());
					//vecteur AB
					Point vectAB = Point();
					vectAB.setx(segmentTable[1].getorigine().getx() - segmentTable[0].getorigine().getx());
					vectAB.sety(segmentTable[1].getorigine().gety() - segmentTable[0].getorigine().gety());
					//equation droite
					float gamma = -vectAB.getx()*segmentTable[1].getorigine().getx() -vectAB.gety()*segmentTable[1].getorigine().gety();
					// calcul du point C
					float xc = (-(float)vectAB.gety()*(float)segmentTable[2].getorigine().gety()-gamma)/(float)vectAB.getx();
					cout<<xc;
					Point C = Point ();
					C.setx(xc);
					C.sety(segmentTable[2].getorigine().gety());
					rectangle.setC(C);
				}
			}
		}
	}
	return est_rectangle;
}

//=========== ANALYSE POLYGONE ================================

bool trouverpolygone (LigneBrisee ligne, Polygone& polygone, int W, int H, int ecartmax){
	//booleen retourne
	bool est_polygone = true;

	vector<Segment> table = ligne.getTable();
	int reference = 0;

	//forme fermee
	if (IsClosedLigne (ligne, W, ecartmax))
	{
		//definition de la taille reference
		for (int i=0; (unsigned)i<table.size(); i++)
		{
			reference += distanceP(table[i].getorogine(), table[i].getextremite(), W, H);
		}
		reference = reference / table.size();
		//comparaison de la reference avec les autres segments
		for (int i=0; (unsigned)i<table.size(); i++)
		{
			if (!(reference - distanceP(table[i].getorogine(), table[i].getextremite(), W, H) <= ecartmax))
			{
				est_polygone = false;
			}
		}
	} else {est_polygone = false;}
	//definition du polygone si c'en est un
	if (est_polygone)
	{
		polygone.setPremier(table[0].getorogine());
		polygone.setDirection(table[0].getextremite() - table[0].getorogine());
		polygone.setSommets(table.size());
	}
	return est_polygone;
}
