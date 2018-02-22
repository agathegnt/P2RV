# trouverformes.cpp

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
		distot += distance(pointemp, nuage[k]);
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

bool trouvercercle(Trait nuage, float distancemax) {
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

bool trouverarc(Trait nuage, float distancemax,W,H) {
	int j = nuage.length();
	float distot = 0.;
	float distmoy;
	Point centre;
	for (int k = 1; k < j-1; k++) : {
		centre = Point(((k-1)*centre+triangularisation2D(nuage[0],nuage[J-1],nuage[k]))/k);
	}
	for (int k = 0; k < j; k++) : {
		distmoy = (k*distmoy + distance(centre, nuage[k]) / (k + 1);
	}
	for (int k = 0; k < j; k++) : {
		distot += sqrt((distance(centre, nuage[k]) - distmoy)**2);
	}
	if (distancemax > distot) {
		return true;
	}
	else { return false; }
}

Point triangularisation2D(Point P1, Point P2, Point P3) {
	float distance = distanceP(P1, P2,W,H);
	float epsilon;
	Point P1P2 = Point(P1.getx-P2.getx,P1.gety-P2.gety,0);
	Point Pmid = (P1 + P2) / 2;
	Point VectCentre = P1P2.vectoriel(Point(0, 0, 1));
	VectCentre.normalize;
	while (distanceP(Pmid, P3,W,H) > 2*epsilon) {
		if (distanceP(Pmid - epsilon * VectCentre, P3,W,H) < distanceP(Pmid, P3,W,H)) {
			Pmid = Pmid - epsilon* VectCentre;
		}
		else{ Pmid = Pmid + epsilon * VectCentre; }
	}
	return Pmid;
}

Point triangularisation3D(Point P1, Point P2, Point P3) {
	float distance = distanceP(P1, P2,W,H);
	float epsilon;
	Point P1P2 = Point(P1.getx - P2.getx, P1.gety - P2.gety, P1.getz-P2.getz);
	Point Pmid = (P1 + P2) / 2;
	Point P3Pmid = Point(P3.getx - Pmid.getx, P3.gety - Pmid.gety, P3.getz - Pmid.getz);
	Point vectyol = P1P2.vectoriel(P3Pmid);
	Point VectCentre = vectyol.vectoriel(P1P2);
	VectCentre.normalize;
	while (distanceP(Pmid, P3,W,H) > 2 * epsilon) {
		if (distanceP(Pmid - epsilon * VectCentre, P3,W,H) < distanceP(Pmid, P3,W,H)) {
			Pmid = Pmid - epsilon * VectCentre;
		}
		else { Pmid = Pmid + epsilon * VectCentre; }
	}
	Return Pmid;
}

float distance(Point P1, Point P2) {
	return sqrt((P1.position[0] - P2.position[0] + P1.position[1] - P2.position[1] + P1.position[2] - P2.position[2])**2);
}

Point::vectoriel(Point P1) {
	return Point(this.y*P1.z - this.z*P1.gety(), this.z*P1.x - this.x*P1.getz(), this.x*P1.y - this.y*P1.getx());
}

Point::normalize() {
	return Point(this.x / sqrt(this.x**2 + this.y**2 + this.z**2), this.y / sqrt(this.x**2 + this.y**2 + this.z**2), this.z / sqrt(this.x**2 + this.y**2 + this.z**2));
}