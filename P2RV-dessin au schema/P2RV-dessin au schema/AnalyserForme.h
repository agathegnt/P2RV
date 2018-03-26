#pragma once

#include "Cercle.h"
#include "Arc.h"
#include "Trait.h"
#include "Segment.h"
#include "LigneBrisee.h"
#include "Rectangle.h"
#include "Polygone.h"

//fonctions utiles
float distanceP(Point, Point, int, int);
bool IsPerpendicular (Forme, Segment);
bool IsParallel (Forme, Segment);
bool IsClosed (Trait, int, int);
bool IsClosedLigne (LigneBrisee, int, int);


//analyse segment
float trouversegment(Trait, int, int);


//analyse cercle
float trouvercercle(Trait, Cercle&, int, int);

//analyse ligne brisee
float trouverlignebrisee(Trait, LigneBrisee&, int, int, int, int);
void LisseLigneBrisee(LigneBrisee&, int, int, int);

//analyse rectangle
bool trouverrectangle (LigneBrisee, Rectangle&, int, int, int);

//analyse polygone
bool trouverpolygone (LigneBrisee, Polygone&, int, int, int);

//recherche de liens entre les formes
int cherchevec(Point, vector<Point>);
Point ajoutpointconfondu(Point*, vector<Forme*>, int, int, int, int);
Point ajoutperpendicularite(Segment, vector<Forme*>, bool, int, int, int);
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);