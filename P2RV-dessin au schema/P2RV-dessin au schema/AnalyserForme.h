#pragma once

#include "Cercle.h"
#include "Arc.h"
#include "Trait.h"
#include "Segment.h"
#include "LigneBrisee.h"
#include "Rectangle.h"
#include "Polygone.h"

float distanceP(Point, Point);
bool IsPerpendicular (Forme, Segment);
bool IsParallel (Forme, Segment);
bool IsClosed (Trait, int, int);
bool trouversegment(Trait, int, int, int);
bool trouvercercle(Trait, Cercle&, int, int, int);

int cherche_point_vec(Point, vector<Point>);
int cherche_segment_vec(Segment, vector<Forme*>);
Point ajoutpointconfondu(Point*, vector<Forme*>, int, int, int, int);
<<<<<<< HEAD
Point ajoutperpendicularite(Segment, bool, vector<Forme*>, int, int, int, int);
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);
=======
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);
>>>>>>> b534fb6b3a4aa51e6ac9e3e187403e2f67977150
