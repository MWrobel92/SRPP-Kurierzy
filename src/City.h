#pragma once
#include <istream>

class City
{
public:
	City(int id) : id(id) {};
	~City();
	int id;
	int x, y;
	double angle;
	double distanceToCenter;
	double distanceTo(City* city);
	bool operator==(City& secondCity);

	/// Ta funkcja wylicza dystans do magazynu i kat nachylenia wzgledem "osi x".
	void setParameters(City* warmhouse);

};

std::istream& operator>>(std::istream& is, City& city);

