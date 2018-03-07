#include "Forme.h"

//===========SEGMENT===============================
//Constructeur
Segment::Segment(){
	origine = Point();
	extremite = Point();
}

Segment::Segment(Point o, Point e){
	origine = o;
	extremite = e;
}

//Getters/Setters
Point Segment::getorogine(){
	return origine;
}
void Segment::setorogine(Point o){
	origine = o;
}
Point Segment::getextremite(){
	return extremite;
}
void Segment::setextremite(Point e){
	extremite = e;
}

//fonction pour tracer la Forme
void Segment::tracer(){
	glBegin(GL_LINES);
		glColor3f(1., 0., 0.);
		glVertex2f(origine.getx(), origine.gety());
		glVertex2f(extremite.getx(), extremite.gety());
	glEnd();
}


//===========TRAIT================================
//Constructeur
Trait::Trait(){
	table = vector<Point>(0);
}

//Getters
vector<Point> Trait::getTable  ()
{
	return table;
}

//ajoute un point au vecteur de points
void Trait::ajout(Point p){
	table.push_back(p);
}

//fonction pour tracer la Forme
void Trait::tracer(){
	int taille = table.size();
	for (int i = 0; i < taille; i++)
	{
		glBegin(GL_POINTS);
			glColor3f(1., 1., 1.);
			glVertex2f(table[i].getx(), table[i].gety());
		glEnd();
	}

}


//===========ARC==================================
Arc::Arc(Point c, float r, float o, float e){
	centre = c;
	rayon = r;
	if(o<e){
		angle1 = o;
		angle2 = e;
	}else{
		angle1 = e;
		angle2 = o;
	}
}

void Arc::tracer(){
	float angle = angle1;
	for(int i=0; i<100; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		angle = angle+(angle2-angle1)/100;
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		glEnd();
	}
}


//===========CERCLE===============================
//Constructeur
Cercle::Cercle(){
	centre = Point();
	rayon = 0;
}

Cercle::Cercle(Point p, float r){
	centre = p;
	rayon = r;
}

Point Cercle::getcentre(){
	return centre;
}
void Cercle::setcentre(Point p){
	centre = p;
}
float Cercle::getrayon(){
	return rayon;
}
void Cercle::setrayon(float r){
	rayon = r;
}

//fonction pour tracer la Forme
void Cercle::tracer(){
	glBegin(GL_POLYGON);
	float angle = 0;
	for(int i=0; i<100; i++)
	{
		glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
		angle = angle+2*M_PI/100;
	}
	glEnd();
}

//Définition de plan pour tracé:

Plan defplan(){
	Point P1;
	Point P2;
	Point P3;
	bool validation =false;
	int x1,y1,z1;
	int x2,y2,z2;
	int x3,y3,z3;

	while(!validation){
		cout<<"P1= ("<<x1<<","<<y1<<","<<z1<<")"<<endl;
		cin>>"(">>x1>>",">>y1>>",">>z1>>")">>endl;
		P1 = Point(x1,y1,z1);
		cout<<"P2= ("<<x2<<","<<y2<<","<<z2<<")"<<endl;
		cin>>"(">>x2>>",">>y2>>",">>z2>>")">>endl;
		P2 = Point(x2,y2,z2);
		cout<<"P3= ("<<x3<<","<<y3<<","<<z3<<")"<<endl;
		cin>>"(">>x3>>",">>y3>>",">>z3>>")">>endl;
		P3 = Point(x3,y3,z3);

		cin>>validation>>endl;
		if(P1==P2 or P2==P3 or P3==P1){
			validation=false;
			cout<<"Vos points ne définissent pas un plan, veuillez les changer"<<endl;}
	}

	Point P1P2 = P2-P1;
	Point P3P1 = P3-P1;

	Point normale = P1P2.ProdVect(P3P1);
	
	return Plan(P1,normale);
}