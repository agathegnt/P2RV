#include "AnalyserForme.h"


//=========== FONCTIONS UTILES ================================

//Fonction de distance entre deux points
float distanceP(Point P1, Point P2, int W, int H) {
	return sqrt((P1.getx()*W/2 - P2.getx()*W/2)*(P1.getx()*W/2 - P2.getx()*W/2) + (P1.gety()*H/2 - P2.gety()*H/2)*(P1.gety()*H/2 - P2.gety()*H/2));
}


//retourne vrai si les deux segments passes en arguments sont presques perpendiculaires
bool IsPerpendicular (Forme f1, Segment f2)
{
	bool perpendicular = false;

    //calcul du produit scalaire
		cout<<f1.getextremite().getx()<<", "<<f1.getextremite().gety()<<endl;
    Point vector1 = f1.getextremite()-f1.getorigine();
    Point vector2 = f2.getextremite()-f2.getorigine();
    float prod_scal = (float)(vector1.getx())*(float)(vector2.getx()) + (float)(vector1.gety())*(float)(vector2.gety());

    if (prod_scal < 0.00000001 && prod_scal > -0.000000001)
    {
		perpendicular = true;
    }
	return perpendicular;
}


//retourne vrai si les deux segments passes en arguments sont presques parall�les
bool IsParallel (Forme f1, Segment f2)
{
	//calcul du produit scalaire
	Point vector1 = f1.getextremite()-f1.getorigine();
	Point vector2 = f2.getextremite()-f2.getorigine();
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
		//si les deux extremites du trait sont proches, alors la forme est presque fermee
		if (vector.norme()*W<=distancemaxclosed)
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

//=========== ANALYSE SEGMENT ================================

//determine si un trait est presque un segment ou non
float trouversegment(Trait trait, int W, int H) {
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float AB = distanceP(nuage[0], nuage[j-1], W, H);
	int ABcarre = AB*AB;
	int AB2 = 2*AB;
	float BC;
	float AC;
	Point pointemp;
	//pour chaque point du trait
	for (int k = 0; k < j; k++){
		BC = distanceP(nuage[k], nuage[j-1], W, H);
		AC = distanceP(nuage[k], nuage[0], W, H);
		//calcule la distance entre le point consid�r� et le segment reliant les extr�mit�s du trait et l'ajoute a distot
		distot += sqrt(abs(AC*AC - ((ABcarre+AC*AC-BC*BC) / AB2) * ((ABcarre+AC*AC-BC*BC) / AB2)));
	}
	/* //on accepte une erreur plus importante si le trait est plus long, d'ou la multiplication par AB
	if (distancemaxsegment*AB > distot) {
		return true;
	}
	else { return false; }*/
	return distot/AB;
}

//recherche les perpendicularites entre un segment et les autres segments de la liste
Point ajoutperpendicularite(Segment seg, vector<Forme*> liste, bool origine, int n, int W, int H){
	//parcours des segments de la liste
	for (int i = 0; i < n-1; i++)
	{
		if(liste[i]->gettype()==SEGMENT){
			// si les deux segments sont presque perpendiculaires
			if(IsPerpendicular (*liste[i], seg)){
				cout<<"orthogonalite a i = "<<i<<endl;
				Point pointinterm;
				Point vec_dir_seg;
				Point vec_ortho;
				vec_dir_seg = (liste[i]->getextremite()-liste[i]->getorigine())/distanceP(liste[i]->getextremite(), liste[i]->getorigine(), W, H);
				vec_ortho.setx(vec_dir_seg.gety());
				vec_ortho.sety(-vec_dir_seg.getx());
				if(origine){

					pointinterm = seg.getextremite() + distanceP(seg.getextremite(), seg.getorigine(), W, H)*vec_ortho;
				}else{
					pointinterm = seg.getorigine() + distanceP(seg.getextremite(), seg.getorigine(), W, H)*vec_ortho;
				}
				return pointinterm;
			}
		}
	}
	// si il n'y a pas d'autres segments ou si ils ne sont pas perpendiculaires
	return Point(1000, 1000, W, H);
}

Segment AnalyseSegment(Segment* seg, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	Point origine = seg->getorigine();
	Point extremite = seg->getextremite();
	bool or = false;
	bool ex = false;
	bool orthogonalise = false;
	Segment newseg;
	newseg.setorigine(origine);
	newseg.setextremite(extremite);
	//recherche de points

	origine = ajoutpointconfondu(&(seg->getorigine()), liste, n, distancemaxpoints, W, H);
	if(origine.getx()<1){
		or = true;
		newseg.setorigine(origine);
	}

	extremite = ajoutpointconfondu(&(seg->getextremite()), liste, n, distancemaxpoints, W, H);
	if(extremite.getx()<1){
		ex = true;
		newseg.setextremite(extremite);
	}

	//si pas trouves, recherche de perpendiculaire
	if(!or){
		origine = ajoutperpendicularite(*seg, liste, true, n, W, H);
		if(origine.getx()<1){
			or = true;
			orthogonalise = true;
			newseg.setorigine(origine);
		}
	}
	if(!ex && !orthogonalise){
		extremite = ajoutperpendicularite(*seg, liste, false, n, W, H);
		if(extremite.getx()<1){
			ex = true;
			newseg.setextremite(extremite);
		}
	}
	//si pas de points trouves, recherche de paralleles
	//TO DO
	return newseg;
}

//=========== ANALYSE CERCLE ================================

//determine si un trait est presque un cercle ou non, et, si oui, met ce cercle dans le parametre cercle
float trouvercercle(Trait trait, Cercle& cercle, int W, int H) {
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float distmoy = 0.;
	Point centre=Point();
	//on trouve le barycentre des points du trait ; il servira de centre
	for (int k = 0; k < j; k++){
		centre.setx((nuage[k].getx() + k * centre.getx()) / (k + 1));
		centre.sety((nuage[k].gety() + k * centre.gety()) / (k + 1));
	}
	//on calcule la distance moyenne entre le barycentre et les points du trait
	for (int k = 0; k < j; k++){
		distmoy += distanceP(centre, nuage[k], W, H);
	}
	distmoy = distmoy/j;
	//on calcule la somme des ecarts a la distance moyenne
	for (int k = 0; k < j; k++){
		distot += abs((distanceP(centre, nuage[k], W, H)-distmoy));
	}
	/*//si cet ecart est suffisamment petit, on a bien un cercle
	if (distancemaxcercle > distot) {
		cercle.setcentre(centre);
		cercle.setrayon(distmoy*2/W);
		return true;
	}
	else { return false; }*/
	cercle.setcentre(centre);
	cercle.setrayon(distmoy*2/W);
	//on renvoie un float donnant l'ecart du cercle au trait initial
	return distot/(10*nuage.size());
}

//=========== ANALYSE LIGNE BRISEE ================================

//determine si un trait est une ligne brisee ou non, et, si oui, met cette ligne dans le parametre ligne
float trouverlignebrisee(Trait trait, LigneBrisee& ligne, int distanceminligne, int distancemaxsegment, int W, int H) {
	//booleen retourne
	//bool estLigne = false;
	float errtot = 0;
	float errtmp = 0;

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
		errtmp = trouversegment(trait_tmp, W, H);
		if (errtmp>distancemaxsegment)
		{

			//on cree un segment avec les points precedents
			Segment segment_tmp = Segment(nuage[debut], nuage[cpt-1]);
			//ajout de ce segment a la ligne BRISEE ssi il est suffisemment long
			if (distanceP(nuage[debut],nuage[cpt-1],W,H) > distanceminligne)
			{
				errtot += errtmp;
				ligne.ajoutSegment(segment_tmp);
				//estLigne = true;
			}
			//reinitialisation des donnees temporaires
			debut = cpt;
			trait_tmp = Trait();
			trait_tmp.ajout(nuage[debut]);
		}
		else if (cpt == (taille-1))
		{
			errtot += errtmp;
			//on cree un segment avec les derniers points
			Segment segment_tmp = Segment(nuage[debut], nuage[cpt]);
			//ajout de ce segment a la ligne brisee ssi il est suffisemment long
			if (distanceP(nuage[debut],nuage[cpt],W,H) > distanceminligne)
			{
				ligne.ajoutSegment(segment_tmp);
				//estLigne = true;
			}
		}
		//incrementation du compteur
		cpt += 1;
	}
	//return estLigne;
	return errtot/(ligne.getTable().size());
}

// fonction qui relie les segments d'une ligne brisee
void LisseLigneBrisee(LigneBrisee& ligne, int distancemaxclosed, int W, int H){
	int taille = (ligne.getTable()).size();
	Point p = Point();
	Point p1 = Point();
	Point p2 = Point();
	//parcours des segments de la ligne brisee
	for (int i = 0; i < taille-1; i++)
	{
		//calcul du point moyen entre l'extremite du segment et l'origine du suivant
		p1=ligne.getTable()[i].getextremite();
		p2=ligne.getTable()[i+1].getorigine();
		p=(p1+p2)/2;
		//mise a jour de l'extremites et l'origine avec ce point moyen
		ligne.setpoint(false, i, p);
		ligne.setpoint(true, i+1, p);
	}
	// si la ligne brisee est fermee, on relie le debut et la fin
	p1=ligne.getTable()[taille-1].getextremite();
	p2=ligne.getTable()[0].getorigine();
	if(distanceP(p1, p2, W, H)<distancemaxclosed){
		//calcul du point moyen
		p=(p1+p2)/2;
		//mise a jour de l'extremite et l'origine avec ce point moyen
		ligne.setpoint(false, taille-1, p);
		ligne.setpoint(true, 0, p);
	}
}

//=========== ANALYSE RECTANGLE ================================

//determine si une ligne brisee est un rectangle ou non, et, si oui, met ce rectangle dans le parametre rectangle
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
				//et si les deux premiers segments sont perpendiculaires
				if (IsPerpendicular (segmentTable[0], segmentTable[1]))
				{
					est_rectangle = true;

					//parametrage du point A
					rectangle.setA(segmentTable[0].getorigine());
					//parametrage du point B
					rectangle.setB(segmentTable[1].getorigine());
					float xb = segmentTable[1].getorigine().getx();
					float yb = segmentTable[1].getorigine().gety();
					//parametrage du point C
					Point C = Point ();
					//vecteur AB
					Point vectAB = Point();
					vectAB.setx(xb - segmentTable[0].getorigine().getx());
					vectAB.sety(yb - segmentTable[0].getorigine().gety());
					//equation droite perpendiculaire a AB passant par B
					float gamma = -vectAB.getx()*xb -vectAB.gety()*yb;
					/*ESSAI D'AMELIORATION
					//longueur du deuxieme cote
					float dist = distanceP(segmentTable[1].getorigine(), segmentTable[2].getorigine(), W, H);
					//calcul du point d'intersection de cette droite et du cercle de centre B et de rayon BC
					float a = 1.0 + (-(float)vectAB.getx()/(float)vectAB.gety())*(-(float)vectAB.getx()/(float)vectAB.gety());
					float b = 2.0 * ((-(float)vectAB.getx()/(float)vectAB.gety()) * (-gamma/(float)vectAB.gety()-yb)-xb);
					float c = xb*xb + (-gamma/(float)vectAB.gety()-yb)*(-gamma/(float)vectAB.gety()-yb)-dist*dist;
					float delta = b * b - 4 * a * b;
					//on obtient 2 solutions
					if (delta > 0)
					{
						float xc1 = (-b - (float)sqrt(delta)) / (2 * a);
						float yc1 = a * xc1 + b;
						float ecart1 = sqrt((xc1*W/2 - segmentTable[2].getorigine().getx()*W/2)*(xc1*W/2 - segmentTable[2].getorigine().getx()*W/2)
							+ (yc1*H/2 - segmentTable[2].getorigine().gety()*H/2)*(yc1*H/2 - segmentTable[2].getorigine().gety()*H/2));
						cout<<ecart1<<endl;

						float xc2 = (-b + (float)sqrt(delta)) / (2 * a);
						float yc2 = a * xc2 + b;
						float ecart2 = sqrt((xc2*W/2 - segmentTable[2].getorigine().getx()*W/2)*(xc2*W/2 - segmentTable[2].getorigine().getx()*W/2)
							+ (yc2*H/2 - segmentTable[2].getorigine().gety()*H/2)*(yc2*H/2 - segmentTable[2].getorigine().gety()*H/2));
						cout<<ecart2<<endl;
						//on choisit la solution la plus proche du point C d'origine
						if (ecart1 <= ecart2)
						{
							C.setx(xc1);
							C.sety(yc1);
						}
						else
						{
							C.setx(xc2);
							C.sety(yc2);
						}
					}
					else
					{
						float xc = (-(float)vectAB.gety()*(float)segmentTable[2].getorigine().gety()-gamma)/(float)vectAB.getx();
						C.setx(xc);
						C.sety(segmentTable[2].getorigine().gety());
					}*/
					float xc = (-(float)vectAB.gety()*(float)segmentTable[2].getorigine().gety()-gamma)/(float)vectAB.getx();
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

//determine si une ligne brisee est un polygone regulier ou non, et, si oui, met ce polygone dans le parametre rectangle
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
			reference += distanceP(table[i].getorigine(), table[i].getextremite(), W, H);
		}
		reference = reference / table.size();
		//comparaison de la reference avec les autres segments
		for (int i=0; (unsigned)i<table.size(); i++)
		{
			if (!(reference - distanceP(table[i].getorigine(), table[i].getextremite(), W, H) <= ecartmax))
			{
				est_polygone = false;
			}
		}
	} else {est_polygone = false;}
	//definition du polygone si c'en est un
	if (est_polygone)
	{
		polygone.setPremier(table[0].getorigine());
		polygone.setDirection(table[0].getextremite() - table[0].getorigine());
		polygone.setSommets(table.size());
	}
	return est_polygone;
}

//=========== RECHERCHES DE LIENS ENTRE LES FORMES ================================

//cherche pres de quels points importants de la liste de formes se trouve p, et retourne le point le plus interessant (si il existe)
Point ajoutpointconfondu(Point* p, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	vector<Point> points;
	vector<int> indpoints;
	int j = 0;
	Point pointinterm;
	//parcours de la liste de formes
	for (int i = 0; i < n-1; i++)
	{
		switch ((liste[i]->gettype()))
		{
		case SEGMENT:
			pointinterm = liste[i]->getextremite();
			// si l'extremite est proche du point P
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				j = cherchevec(pointinterm, points);
				// si ce point appartient deja a la liste, on incremente son compteur
				if(j>=0){
					indpoints[j]++;
				// sinon ajout de ce point a la liste de point
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
			// si l'origine est proche du point P
			pointinterm = liste[i]->getorigine();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				j = cherchevec(pointinterm, points);
				// si ce point appartient deja a la liste, on incremente son compteur
				if(j>=0){
					indpoints[j]++;
				// sinon ajout de ce point a la liste de point
				}else{
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
		break;
		case CERCLE:
		case ARC:
			// si le centre est proche du point P
			pointinterm = liste[i]->getcentre();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				j = cherchevec(pointinterm, points);
				// si ce point appartient deja a la liste, on incremente son compteur
				if(j>=0){
					indpoints[j]++;
				// sinon ajout de ce point a la liste de point
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
	// si il n'y a aucun point remarquable proche de P
	if(points.size()==0){
		return Point(1000, 1000, W, H);
	// sinon on choisit le point dont le compteur est le plus haut
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
		return pointinterm;
	}
}
