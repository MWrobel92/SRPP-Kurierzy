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

	//Wspó³rzedne wzglêdem magazynu
	int xx = x - warmhouse->x;
	int yy = -(y - warmhouse->y);

	// Odleg³oœæ od zera  
	distanceToCenter = sqrt(xx*xx+yy*yy);   
    
	if (distanceToCenter == 0) {
		angle = 0;
		return; // ¯eby nie by³o dzielenia przez zero
	}

    // Sinus kata
    double sinus = yy/distanceToCenter;
	const double pi = 3.14159;
    
    // Dokladny kat (miara ³ukowa)
    if (yy > 0) {
        if (xx > 0) { // I æwiatrka
            angle = asin(sinus);
        }
        else { // II æwiartka
            angle = pi - asin(sinus);
        }
    }
    else {
        if (xx < 0) { // III æwiatrka
            angle = pi - asin(sinus);
        }
        else { // IV æwiartka
            angle = 2*pi + asin(sinus);
        }
    }
}

std::istream& operator>>(std::istream& is, City& city) {
	is >> city.x;
	is >> city.y;
	return is;
}
