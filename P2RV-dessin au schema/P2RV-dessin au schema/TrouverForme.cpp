#trouverformes.cpp

#include "Forme.h"

bool trouversegment(Trait nuage, float distancemax) {
	int j = nuage.length();
	float distot = 0.;
	float AB = distance(nuage[0],nuage[j]);
	float BC;
	float AC;
	float posrel;
	Point pointemp;
	for (int k = 0; k < j; k++) : {
		BC = distance(nuage[k], nuage[j]);
		AC = distance(nuage[k], nuage[0];
		posrel = AC / (AC + BC);
		pointemp = Point(nuage[0].position[0] + (nuage[j].position[0] - nuage[0].position[0])*posrel, nuage[0].position[1] + (nuage[j].position[1] - nuage[0].position[1])*posrel, nuage[0].position[2] + (nuage[j].position[2] - nuage[0].position[2])*posrel);
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

	int j = nuage.length();
	float distot = 0.;
	float distmoy;
	Point centre;
	for (int k = 0; k < j; k++) : {
		centre = Point((nuage[k].position[0] + k * pointemp.position[0]) / k + 1, (nuage[k].position[1] + k * pointemp.position[1]) / k + 1, (nuage[k].position[2] + k * pointemp.position[2]) / k + 1);
	}
	for (int k = 0; k < j; k++) : {
		distmoy = (k*distmoy + distance(centre, nuage[k])/(k+1);
	}
	for (int k = 0; k < j; k++) : {
		distot += sqrt((distance(centre,nuage[k])-)**2);
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

	int j = nuage.length();
	float distot = 0.;
	float distmoy;
	Point centre;
	}
	for (int k = 0; k < j; k++) : {
		distmoy = (k*distmoy + distance(centre, nuage[k]) / (k + 1);
	}
	for (int k = 0; k < j; k++) : {
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

float distance(Point P1, Point P2) {
	return sqrt((P1.position[0] - P2.position[0] + P1.position[1] - P2.position[1] + P1.position[2] - P2.position[2])**2);
}