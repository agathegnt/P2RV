#pragma once

#include "Cercle.h"
#include "Arc.h"
#include "Trait.h"
#include "Segment.h"
//#include "LigneBrisee.h"

float distanceP(Point, Point);
bool IsPerpendicular (Forme, Segment);
bool IsParallel (Forme, Segment);
bool IsClosed (Trait, int, int);
bool trouversegment(Trait, int, int, int);
bool trouvercercle(Trait, Cercle&, int, int, int);

int cherchevec(Point, vector<Point>);
Point ajoutpointconfondu(Point*, vector<Forme*>, int, int, int, int);
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);