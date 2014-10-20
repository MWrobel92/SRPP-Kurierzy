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

void Route::draw(BITMAP* bmp, int x, int y, int routeID, int routeCount) {
	City* prev = route[route.size() - 1];
	int brightness = routeID * 255 / routeCount;
	int routeColor = makecol(255, 255 - brightness, brightness);
	for (int i = 0; i < route.size(); ++i) {
		City* current = route[i];
		
		line(bmp, prev->x, prev->y, current->x, current->y, routeColor);
		int cityColor = makecol(0, 255, 0);
		if (i == 0) cityColor = makecol(255, 255, 255);
		circle(bmp, current->x, current->y, 3, cityColor);
		textprintf_ex(bmp, font, current->x, current->y,
			cityColor, makecol(0, 0, 0), "%i", current->id);

		prev = current;
	}
}

std::ostream& operator<<(std::ostream& os, Route& route) {
	for (int i = 0; i < route.route.size(); ++i) {
		os << route.route[i]->id << ' ';
	}
	os << '0';
	return os;
}
