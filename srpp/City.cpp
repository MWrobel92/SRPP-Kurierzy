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

std::istream& operator>>(std::istream& is, City& city) {
	is >> city.x;
	is >> city.y;
	return is;
}
