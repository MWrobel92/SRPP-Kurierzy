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

	City* getCityAt(int id);
	void setCityAt(City* toSet, int id);
	void moveCity(int position, int newPosition);

	void removeCityAt(int id);

	//d³ugoœæ od pierwszego do ostatniego miasta, bez powrotu
	double getPartialLength();

	//odwróæ podœcie¿kê z przedzia³u [i, j]
	//np. dla œcie¿ki 0 1 2 3 4 5 po wykonaniu z parametrami (2, 5)
	//wynik jest 0 1 5 4 3 2
	void swapSubroute(int i, int j);

	//poodwracaj podœcie¿ki utworzone przez ciêcie w punktach i j k
	//m okreœla przekszta³cenie:
	//4 = odwróæ wszystko (od i do k)
	//2 = odwróæ lew¹ (od i do j)
	//1 = odwróæ praw¹ (od j+1 do k)
	void perform3optSwap(int i, int j, int k, int m);

	friend std::ostream& operator<<(std::ostream& os, Route& route);

private:
	std::vector<City*> route;
};

std::ostream& operator<<(std::ostream& os, Route& route);
