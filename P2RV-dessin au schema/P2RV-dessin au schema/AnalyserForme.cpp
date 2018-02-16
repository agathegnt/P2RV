#include "AnalyserForme.h"

float distanceP(Point P1, Point P2, int W, int H) {
	return sqrt((P1.getx()*W/2 - P2.getx()*W/2)*(P1.getx()*W/2 - P2.getx()*W/2) + (P1.gety()*H/2 - P2.gety()*H/2)*(P1.gety()*H/2 - P2.gety()*H/2));
}

bool IsPerpendicular (Segment f1, Segment f2)
{
	bool perpendicular = false;

    //calcul du produit scalaire
    Point vector1 = f1.getextremite()-f1.getorogine();
    Point vector2 = f2.getextremite()-f2.getorogine();
    int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

    if (prod_scal < 0,01)
    {
      perpendicular = true;
    }

	return perpendicular;
}

bool IsParallel (Segment f1, Segment f2)
{
  bool parallel = false;

  //calcul du produit scalaire
  Point vector1 = f1.getextremite()-f1.getorogine();
  Point vector2 = f2.getextremite()-f2.getorogine();
  int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

  //compare le produit scalaire au produit des normes des vecteurs
  if (prod_scal - vector1.norme()*vector2.norme()< 0,01)
  {
      parallel = true;
  }

  return parallel;

}

//determine si la forme est fermee ou pas
bool IsClosed (Trait trait, int W)
{
  bool closed = false;
  vector<Point> table = trait.getTable();

  //le trait doit etre d'une taille superieure a 5
  if (table.size()>5)
  {
      Point vector = table[table.size()-1] - table[0];
      if (vector.norme()*W<=20)
      {
        closed = true;
      }
  }
  return closed;
}

bool trouversegment(Trait trait, float distancemax, int W, int H) {
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float AB;
	AB = distanceP(nuage[0], nuage[j-1], W, H);
	int ABcarre = AB*AB;
	int AB2 = 2*AB;
	float BC;
	float AC;
	//float posrel;
	Point pointemp;
	for (int k = 0; k < j; k++){
		BC = distanceP(nuage[k], nuage[j-1], W, H);
		AC = distanceP(nuage[k], nuage[0], W, H);
		distot+=sqrt(abs(AC*AC-((ABcarre+AC*AC-BC*BC)/AB2)*((ABcarre+AC*AC-BC*BC)/AB2)));
	}
	if (distancemax*AB > distot) {
		return true;
	}
	else { return false; }
}

bool trouvercercle(Trait trait, Cercle& cercle, float distancemax, int W, int H) {
	vector<Point> nuage = trait.getTable();
	int j = nuage.size();
	float distot = 0.;
	float distmoy = 0.;
	Point centre=Point();
	for (int k = 0; k < j; k++){
		centre.setx((nuage[k].getx() + k * centre.getx()) / (k + 1));
		centre.sety((nuage[k].gety() + k * centre.gety()) / (k + 1));
	}
	for (int k = 0; k < j; k++){
		distmoy += distanceP(centre, nuage[k], W, H);
	}
	distmoy = distmoy/j;
	for (int k = 0; k < j; k++){
		distot += abs((distanceP(centre, nuage[k], W, H)-distmoy));
	}
	if (distancemax > distot) {
		cercle.setcentre(W*centre/2);
		cercle.setrayon(distmoy*2/W);
		return true;
	}
	else { return false; }
}