#pragma once

#include "Cercle.h"
#include "Arc.h"
#include "Trait.h"
#include "Segment.h"

float distanceP(Point, Point);
bool IsPerpendicular (Segment, Segment);
bool IsParallel (Segment, Segment);
bool IsClosed (Trait, int, int);
bool trouversegment(Trait, int, int, int);
bool trouvercercle(Trait, Cercle&, int, int, int);

int cherchevec(Point, vector<Point>);
bool ajoutpoint(Point*, Point*, vector<Forme*>, int, int, int, int);
void AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);