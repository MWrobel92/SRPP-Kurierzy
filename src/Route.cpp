#include "Route.h"


Route::Route(City* startingCity) {
	route.push_back(startingCity);
}

Route::~Route()
{
}

void Route::append(City* city) {
	route.push_back(city);
}

double Route::getLength() {
	double length = 0.0;
	int prev = route.size() - 1;
	for (int i = 0; i < route.size(); ++i) {
		length += route[i]->distanceTo(route[prev]);
		prev = i;
	}
	return length;
}

std::ostream& operator<<(std::ostream& os, Route& route) {
	for (int i = 0; i < route.route.size(); ++i) {
		os << route.route[i]->id << ' ';
	}
	os << '0';
	return os;
}
