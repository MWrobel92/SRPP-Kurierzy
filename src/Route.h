#pragma once
#include <vector>
//#include <allegro.h>
#include <ostream>
#include "City.h"

class Route
{
public:
	Route(City* startingCity);
	Route(const Route& old);
	~Route();

	void append(City* city);
	double getLength();
	int getNumberOfCities();

	City* getCityAt(int id);
	void setCityAt(City* toSet, int id);
	void moveCity(int position, int newPosition);
	void removeCityAt(int id);

	//d³ugoœæ od pierwszego do ostatniego miasta, bez powrotu
	double getPartialLength();
	void removeLast();

	friend std::ostream& operator<<(std::ostream& os, Route& route);

private:
	std::vector<City*> route;
};

std::ostream& operator<<(std::ostream& os, Route& route);
