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

	//d�ugo�� od pierwszego do ostatniego miasta, bez powrotu
	double getPartialLength();

	//odwr�� pod�cie�k� z przedzia�u [i, j]
	//np. dla �cie�ki 0 1 2 3 4 5 po wykonaniu z parametrami (2, 5)
	//wynik jest 0 1 5 4 3 2
	void swapSubroute(int i, int j);

	//poodwracaj pod�cie�ki utworzone przez ci�cie w punktach i j k
	//m okre�la przekszta�cenie:
	//4 = odwr�� wszystko (od i do k)
	//2 = odwr�� lew� (od i do j)
	//1 = odwr�� praw� (od j+1 do k)
	void perform3optSwap(int i, int j, int k, int m);

	friend std::ostream& operator<<(std::ostream& os, Route& route);

private:
	std::vector<City*> route;
};

std::ostream& operator<<(std::ostream& os, Route& route);
