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
	void removeLast();
	double getLength();
	int getNumberOfCities();

	//d³ugoœæ od pierwszego do ostatniego miasta, bez powrotu
	double getPartialLength();

	City* getCityAt(int id);
	void setCityAt(City* toSet, int id);
	void moveCity(int position, int newPosition);

	//odwróæ podœcie¿kê z przedzia³u [i, j]
	//np. dla œcie¿ki 0 1 2 3 4 5 po wykonaniu z parametrami (2, 5)
	//wynik jest 0 1 5 4 3 2
	void swapSubroute(int i, int j);
	
	friend std::ostream& operator<<(std::ostream& os, Route& route);

private:
	std::vector<City*> route;
};

std::ostream& operator<<(std::ostream& os, Route& route);
