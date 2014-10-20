#pragma once
#include <istream>

class City
{
public:
	City(int id) : id(id) {};
	~City();
	int id;
	int x, y;
	double distanceTo(City* city);

};

std::istream& operator>>(std::istream& is, City& city);

