#pragma once

#include "Cercle.h"
#include "Arc.h"
#include "Trait.h"
#include "Segment.h"
#include "LigneBrisee.h"
#include "Rectangle.h"
#include "Polygone.h"

float distanceP(Point, Point, int, int);
bool IsPerpendicular (Forme, Segment);
bool IsParallel (Forme, Segment);
bool IsClosed (Trait, int, int);
bool IsClosedLigne (LigneBrisee, int, int);
float trouversegment(Trait, int, int);
float trouvercercle(Trait, Cercle&, int, int);
float trouverlignebrisee(Trait, LigneBrisee&, int, int, int, int);
void LisseLigneBrisee(LigneBrisee&, int, int, int);
bool trouverrectangle (LigneBrisee, Rectangle&, int, int, int);
bool trouverpolygone (LigneBrisee, Polygone&, int, int, int);


int cherchevec(Point, vector<Point>);
Point ajoutpointconfondu(Point*, vector<Forme*>, int, int, int, int);
Point ajoutperpendicularite(Segment, vector<Forme*>, int, int, int, int);
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);
