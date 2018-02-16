#pragma once

#include "Forme.h"
float distanceP(Point, Point);
bool IsPerpendicular (Segment, Segment);
bool IsParallel (Segment, Segment);
bool IsClosed (Trait, int);
bool trouversegment(Trait, float, int, int);
bool trouvercercle(Trait, Cercle&, float, int, int);