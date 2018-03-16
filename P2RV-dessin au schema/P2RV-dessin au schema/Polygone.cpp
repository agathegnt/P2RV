#include "Polygone.h"

//Constructeur polygone nul
Polygone::Polygone(){
	premier = Point();
	direction = Point();
  sommets = 0;
	type = POLYGONE;
}

//Setters
void Polygone::setPremier (Point p)
{
	premier = p;
}

void Polygone::setDirection (Point d)
{
	direction = d;
}

void Polygone::setSommets (int s)
{
	sommets = s;
}

//fonction pour tracer la forme
void Polygone::tracer(){
  float angle =  (1.0-2.0/sommets)*180;
	glBegin(GL_POLYGON);
		glColor3f(1., 0., 0.);
    //initialisation de x et y
    float x = premier.getx();
    float y = premier.gety();
    //parcours des sommets du polygone en effectuant une rotation
    for (int i=0; i<sommets; i++)
    {
      x += direction.getx()*cos(angle*i)-direction.gety()*sin(angle*i);
      y += direction.getx()*sin(angle*i)+direction.gety()*cos(angle*i);
      glVertex2f(x,y);
    }
	glEnd();
}
