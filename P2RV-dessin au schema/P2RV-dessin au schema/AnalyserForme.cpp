#include "AnalyserForme.h"


//=========== FONCTIONS UTILES ================================

//Fonction de distance entre deux points
float distanceP(Point P1, Point P2, int W, int H) {
	return sqrt((P1.getx()*W/2 - P2.getx()*W/2)*(P1.getx()*W/2 - P2.getx()*W/2) + (P1.gety()*H/2 - P2.gety()*H/2)*(P1.gety()*H/2 - P2.gety()*H/2));
}


//retourne vrai si les deux segments passï¿½s en arguments sont presques perpendiculaires
bool IsPerpendicular (Forme f1, Segment f2)
{
	bool perpendicular = false;

    //calcul du produit scalaire
    Point vector1 = f1.getextremite()-f1.getorigine();
    Point vector2 = f2.getextremite()-f2.getorigine();
    float prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();
    if ((-0.04<prod_scal) && (prod_scal<0,04))
    {
		perpendicular = true;
    }
	return perpendicular;
}


//retourne vrai si les deux segments passï¿½s en arguments sont presques parallï¿½les
bool IsParallel (Forme f1, Segment f2)
{
	//calcul du produit scalaire
	Point vector1 = f1.getextremite()-f1.getorigine();
	Point vector2 = f2.getextremite()-f2.getorigine();
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
		if (vector.norme()*W<=distancemaxclosed)//si les deux extrï¿½mitï¿½s du trait sont proches, alors la forme est presque fermï¿½e
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
	Point debut = table[0].getorogine();
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

//dï¿½termine si un trait est presque un segment ou non
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
		distot += sqrt(abs(AC*AC - ((ABcarre+AC*AC-BC*BC) / AB2) * ((ABcarre+AC*AC-BC*BC) / AB2)));//calcule la distance entre le point considï¿½rï¿½ et le segment reliant les extrï¿½mitï¿½s du trait et l'ajoute ï¿½ distot
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
	for (int k = 0; k < j; k++){//on calcule la somme des ï¿½carts ï¿½ la distance moyenne
		distot += abs((distanceP(centre, nuage[k], W, H)-distmoy));
	}
	if (distancemaxcercle > distot) {//si cet ï¿½cart est suffisamment petit, on a bien un cercle
		cercle.setcentre(centre);
		cercle.setrayon(distmoy*2/W);
		return true;
	}
	else { return false; }
}


//retourne l'indice correspondant si le point existe dans le vector, -1 si non
int cherche_point_vec(Point p, vector<Point> points){
	for (int i = 0; i < (signed)points.size(); i++)
	{
		if(p==points[i]){
			return i;
		}
	}
	return -1;
}

<<<<<<< HEAD
//retourne l'indice correspondant si le Segment existe dans le vector, -1 si non
int cherche_segment_vec(Segment seg, vector<Forme*> segs){
	for (int i = 0; i < (signed)segs.size(); i++)
	{
		if(seg.getorigine().getx()==(*(segs[i])).getorigine().getx() && seg.getorigine().gety()==(*(segs[i])).getorigine().gety() && seg.getextremite().getx()==(*(segs[i])).getextremite().getx() && seg.getextremite().gety()==(*(segs[i])).getextremite().gety()){
			return i;
		}
	}
	return -1;
}

//cherche près de quels points importants de la liste de formes se trouve p, et retourne le point le plus intéressant (si il existe)
=======
//cherche prï¿½s de quels points importants de la liste de formes se trouve p, et retourne le point le plus intï¿½ressant (si il existe)
>>>>>>> b534fb6b3a4aa51e6ac9e3e187403e2f67977150
Point ajoutpointconfondu(Point* p, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	vector<Point> points;//les points dont est proche p
	vector<int> indpoints;//l'importance de ces points : plus important si il est l'extrémité de 3 segments et le centre de 2 cercles
	int j = 0;
	Point pointinterm;
	for (int i = 0; i < n-1; i++)
	{
		switch ((liste[i]->gettype()))
		{
		case SEGMENT://pour chaque segment, on regarde si l'origine et l'extrémité sont proches de p
			pointinterm = liste[i]->getextremite();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){//origine
				j = cherche_point_vec(pointinterm, points);
				if(j>=0){//si le point apparait déjà dans points, on augmente son importance
					indpoints[j]++;
				}else{//sinon, on l'ajoute à points
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
			pointinterm = liste[i]->getorigine();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){//extrémité
				j = cherche_point_vec(pointinterm, points);
				if(j>=0){//si le point apparait déjà dans points, on augmente son importance
					indpoints[j]++;
				}else{//sinon, on l'ajoute à points
					points.push_back(pointinterm);
					indpoints.push_back(1);
				}
			}
		break;
		case CERCLE://pour chaque cercle et arc de cercle, on regarde si le centre est proche de p
		case ARC:
			pointinterm = liste[i]->getcentre();
			if(distanceP(*p, pointinterm, W, H)<distancemaxpoints){
				j = cherche_point_vec(pointinterm, points);
				if(j>=0){//si le point apparait déjà dans points, on augmente son importance
					indpoints[j]++;
				}else{//sinon, on l'ajoute à points
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
	if(points.size()==0){//si il n'y a aucun point proche de p dans les formes existantes
		return Point(10000, 10000, W, H);
	}else{//sinon
		int indice = 0;
		int val = 0;
		for (int i = 0; i < (signed)points.size(); i++)//on cherche quel point est le plus important, ie celui qui apparait dans le plus d'autres formes
		{
			if(indpoints[i]>val){
				val = indpoints[i];
				indice = i;
			}
		}
		pointinterm.setx(points[indice].getx());
		pointinterm.sety(points[indice].gety());
		return pointinterm;//on retourne le point ainsi trouvé
	}
}

Point ajoutperpendicularite(Segment seg, bool quel_point, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	Point pointinterm;
	Segment seginterm;
	vector<Forme*> segs;
	vector<int> indsegs;
	int j = 0;
	for (int i = 0; i < n-1; i++)
	{
		if(liste[i]->gettype()==SEGMENT){//pour chaque segment, on regarde si il est presque perpendiculaire à seg
			if(IsPerpendicular (*liste[i], seg)){
				j = cherche_segment_vec(seginterm, segs);
				if(j>=0){//si le point apparait déjà dans segs, on augmente son importance
					indsegs[j]++;
				}else{//sinon, on l'ajoute à segs
					segs.push_back(liste[i]);
					indsegs.push_back(1);
				}
			}
		}
	}
	if(segs.size()==0){//si seg n'est perpendiculaire à aucun segment existant
		return Point(10000, 10000, W, H);
	}else{//sinon
		cout<<"fait qqch"<<endl;
		int indice = 0;
		int val = 0;
		for (int i = 0; i < (signed)segs.size(); i++)//on cherche
		{
			if(indsegs[i]>val){
				val = indsegs[i];
				indice = i;
			}
		}
		Point p1, p2;
		cout<<(*(segs[indice])).getorigine().getx()<<"              "<<(*(segs[indice])).getextremite().getx()<<endl;
		float l1 = distanceP((*(segs[indice])).getorigine(), (*(segs[indice])).getextremite(), W, H);
		float l2 = distanceP(seg.getorigine(), seg.getextremite(), W, H);
		cout<<"l1="<<l1<<endl;
		if(quel_point){
			cout<<"ancien x = "<<seg.getextremite().getx()<<"ancien y = "<<seg.getextremite().gety()<<endl;
			p1.setx(seg.getextremite().getx()-(l2/l1)*((*(segs[indice])).getextremite().gety()-(*(segs[indice])).getorigine().gety()));
			p1.sety(seg.getextremite().gety()+(l2/l1)*((*(segs[indice])).getextremite().getx()-(*(segs[indice])).getorigine().getx()));
			p2.setx(seg.getextremite().getx()+(l2/l1)*((*(segs[indice])).getextremite().gety()-(*(segs[indice])).getorigine().gety()));
			p2.sety(seg.getextremite().gety()-(l2/l1)*((*(segs[indice])).getextremite().getx()-(*(segs[indice])).getorigine().getx()));
			if(distanceP(seg.getorigine(), p1, W, H)<distanceP(seg.getorigine(), p2, W, H)){
				pointinterm = p1;
			}else{
				pointinterm = p2;
			}
			cout<<"nouveau x = "<<pointinterm.getx()<<"nouveau y = "<<pointinterm.gety()<<endl;
		}else{
			cout<<"ancien x = "<<seg.getorigine().getx()<<"ancien y = "<<seg.getorigine().gety()<<endl;
			p1.setx(seg.getorigine().getx()-(l2/l1)*((*(segs[indice])).getextremite().gety()-(*(segs[indice])).getorigine().gety()));
			p1.sety(seg.getorigine().gety()+(l2/l1)*((*(segs[indice])).getextremite().getx()-(*(segs[indice])).getorigine().getx()));
			p2.setx(seg.getorigine().getx()+(l2/l1)*((*(segs[indice])).getextremite().gety()-(*(segs[indice])).getorigine().gety()));
			p2.sety(seg.getorigine().gety()-(l2/l1)*((*(segs[indice])).getextremite().getx()-(*(segs[indice])).getorigine().getx()));
			if(distanceP(seg.getorigine(), p1, W, H)<distanceP(seg.getorigine(), p2, W, H)){
				pointinterm = p1;
			}else{
				pointinterm = p2;
			}
			cout<<"nouveau x = "<<pointinterm.getx()<<"nouveau y = "<<pointinterm.gety()<<endl;
		}
	}
	return pointinterm;
}

Segment AnalyseSegment(Segment* seg, vector<Forme*> liste, int n, int distancemaxpoints, int W, int H){
	Point origine = seg->getorigine();
	Point extremite = seg->getextremite();
	bool or = false;
	bool ex = false;
	Segment newseg;
	newseg.setorigine(origine);
	newseg.setextremite(extremite);
	//recherche de points
<<<<<<< HEAD
	
	origine = ajoutpointconfondu(&(seg->getorigine()), liste, n, distancemaxpoints, W, H);
=======

	origine = ajoutpointconfondu(&(seg->getorogine()), liste, n, distancemaxpoints, W, H);
>>>>>>> b534fb6b3a4aa51e6ac9e3e187403e2f67977150
	if(origine.getx()<1){
		or = true;
		newseg.setorigine(origine);
	}

	extremite = ajoutpointconfondu(&(seg->getextremite()), liste, n, distancemaxpoints, W, H);
	if(extremite.getx()<1){
		ex = true;
		newseg.setextremite(extremite);
	}

<<<<<<< HEAD
	//si pas trouvés, recherche de perpendiculaire
	/*if(!or){
		origine = ajoutperpendicularite(*seg, true,  liste, n, distancemaxpoints, W, H);
=======
	//si pas trouvï¿½s, recherche de perpendiculaire
	if(!or){
		origine = ajoutperpendicularite(*seg, liste, n, distancemaxpoints, W, H);
>>>>>>> b534fb6b3a4aa51e6ac9e3e187403e2f67977150
		if(origine.getx()<1){
			or = true;
			newseg.setorigine(origine);
		}
	}
	if(!ex){
		extremite = ajoutperpendicularite(*seg, false, liste, n, distancemaxpoints, W, H);
		if(extremite.getx()<1){
			ex = true;
			newseg.setextremite(extremite);
		}
<<<<<<< HEAD
	}*/
	//si pas de points trouvés, recherche de parallèles
=======
	}
	//si pas de points trouvï¿½s, recherche de parallï¿½les


>>>>>>> b534fb6b3a4aa51e6ac9e3e187403e2f67977150

	return newseg;
}


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
				debut = cpt-1;
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

//=========== ANALYSE RECTANGLE ================================

bool estRectangle (LigneBrisee ligne, Rectangle& rectangle, int W, int H, int distancemaxclosed){
	//booleen retourne
	bool est_rectangle = false;
	//table des segments
	vector<Segment> segmentTable = ligne.getTable();

	if (segmentTable.size()==4)
	{
		//forme fermee
		if (IsClosedLigne (ligne, W, distancemaxclosed))
		{
			//si les segments opposes sont paralleles
			if (IsParallel (segmentTable[0], segmentTable[2]) && IsParallel (segmentTable[1], segmentTable[3])
				//et si les deux premiers segments sont perprendiculaires
				&& IsPerpendicular (segmentTable[0], segmentTable[1]))
				{
					est_rectangle = true;
					rectangle.setRef(segmentTable[0].getorogine());
					rectangle.setOppose(segmentTable[2].getorogine());
				}
		}
	}
}

//=========== ANALYSE POLYGONE ================================

bool estPolygone (LigneBrisee ligne, Polygone& polygone, int W, int H, int ecartmax){
	//booleen retourne
	bool est_polygone = true;

	vector<Segment> table = ligne.getTable();
	int reference = 0;

	//forme fermee
	if (IsClosedLigne (ligne, W, ecartmax))
	{
		//definition de la taille reference
		for (int i=0; i<table.size(); i++)
		{
			reference += distanceP(table[i].getorogine(), table[i].getextremite(), W, H);
		}
		reference = reference / table.size();
		//comparaison de la reference avec les autres segments
		for (int i=0; i<table.size(); i++)
		{
			if (reference - distanceP(table[i].getorogine(), table[i].getextremite(), W, H) <= ecartmax)
			{
				est_polygone *= true;
			}
			else {est_polygone *= false;}
		}
	}
	else {est_polygone *= false;}
	//definition du polygone si c'en est un
	if (est_polygone)
	{
		polygone.setPremier(table[0].getorogine());
		polygone.setDirection(table[0].getextremite() - table[0].getorogine());
		polygone.setSommets(table.size());
	}
	return est_polygone;
}
