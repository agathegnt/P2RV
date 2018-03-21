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
bool trouverlignebrisee(Trait trait, LigneBrisee& ligne, int distancemax, int distanceminligne, int W, int H);
LigneBrisee* LisseLigneBrisee(LigneBrisee);
bool trouverrectangle (LigneBrisee ligne, Rectangle& rectangle, int W, int H, int distancemaxclosed);
bool trouverpolygone (LigneBrisee ligne, Polygone& polygone, int W, int H, int ecartmax);


int cherchevec(Point, vector<Point>);
Point ajoutpointconfondu(Point*, vector<Forme*>, int, int, int, int);
Segment AnalyseSegment(Segment*, vector<Forme*>, int, int, int, int);
