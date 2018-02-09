#include "Forme.h"

// dertermine si deux segments sont perpendiculaires
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

bool IsParallel (Segment f1, Segment f2)
{
  bool parallel = false;

  //calcul du produit scalaire
  Point vector1 = f1.getextremite()-f1.getorogine();
  Point vector2 = f2.getextremite()-f2.getorogine();
  int prod_scal = vector1.getx()*vector2.getx() + vector1.gety()*vector2.gety();

  //compare le produit scalaire au produit des normes des vecteurs
  if (prod_scal - vector1.norme()*vector2.norme()< 0,01)
  {
      parallel = true;
  }

  return parallel;

}

//determine si la forme est fermee ou pas
bool IsClosed (Trait trait)
{
  bool closed = false;
  vector<Point> table = trait.getTable();

  //le trait doit etre d'une taille superieure a 5
  if (table.size()>5)
  {
      Point vector = table[table.size()-1] - table[0];
      if (vector.norme()<=5)
      {
        closed = true;
      }
  }
  return closed;
}
