#include "City.h"
#include <cmath>

City::~City()
{
}

double City::distanceTo(City* city) {
	double dx = city->x - x;
	double dy = city->y - y;
	return sqrt(dx * dx + dy * dy);
}

void City::setParameters(City* warmhouse) {

	//Wsp�rzedne wzgl�dem magazynu
	int xx = x - warmhouse->x;
	int yy = -(y - warmhouse->y);

	// Odleg�o�� od zera  
	distanceToCenter = sqrt(xx*xx+yy*yy);   
    
	if (distanceToCenter == 0) {
		angle = 0;
		return; // �eby nie by�o dzielenia przez zero
	}

    // Sinus kata
    double sinus = yy/distanceToCenter;
	const double pi = 3.14159;
    
    // Dokladny kat (miara �ukowa)
    if (yy > 0) {
        if (xx > 0) { // I �wiatrka
            angle = asin(sinus);
        }
        else { // II �wiartka
            angle = pi - asin(sinus);
        }
    }
    else {
        if (xx < 0) { // III �wiatrka
            angle = pi - asin(sinus);
        }
        else { // IV �wiartka
            angle = 2*pi + asin(sinus);
        }
    }
}

std::istream& operator>>(std::istream& is, City& city) {
	is >> city.x;
	is >> city.y;
	return is;
}
