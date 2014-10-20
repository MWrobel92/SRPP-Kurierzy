#pragma once
#include <vector>
#include <allegro.h>
#include <ostream>
#include "City.h"

class Route
{
public:
	Route(City* startingCity);
	~Route();
	void append(City* city);
	void draw(BITMAP* bmp, int x, int y, int routeID, int routeCount);
	double getLength();

	friend std::ostream& operator<<(std::ostream& os, Route& route);
private:
	std::vector<City*> route;
};

std::ostream& operator<<(std::ostream& os, Route& route);
