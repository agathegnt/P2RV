#include "Tests.h"

float distance(Point P1, Point P2) {
	return sqrt((P1.getx() - P2.getx())*(P1.getx() - P2.getx()) + (P1.gety() - P2.gety())*(P1.gety() - P2.gety()));
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

/*bool trouversegment(Trait trait, float distancemax) {
	vector<Point> nuage = trait.gettable();
	int j = nuage.size();
	float distot = 0.;
	float AB = distance(nuage[0], nuage[j-1]);
	float BC;
	float AC;
	float posrel;
	Point pointemp;
	for (int k = 0; k < j; k++){
		BC = distance(nuage[k], nuage[j-1]);
		AC = distance(nuage[k], nuage[0]);
		posrel = AC / (AC + BC);
		pointemp.setx(nuage[0].getx() + (nuage[j].getx() - nuage[0].getx())*posrel);
		pointemp.sety(nuage[0].gety() + (nuage[j].gety() - nuage[0].gety())*posrel);
		distot += distance(pointemp, nuage[k]);
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

bool trouvercercle(Trait trait, float distancemax) {
	vector<Point> nuage = trait.gettable();
	int j = nuage.size();
	float distot = 0.;
	float distmoy = 0;
	Point centre=Point();
	for (int k = 0; k < j; k++){
		centre.setx((nuage[k].getx() + k * centre.getx()) / k + 1);
		centre.sety((nuage[k].gety() + k * centre.gety()) / k + 1);
	}
	for (int k = 0; k < j; k++){
		distmoy = (distmoy + distance(centre, nuage[k]));
	}
	distmoy = distmoy/j;
	for (int k = 0; k < j; k++){
		distot += abs((distance(centre,nuage[k])-distmoy));
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}*/