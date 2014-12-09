#pragma once
#include <istream>
#include "InputData.h"
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

	void setInputData(InputData* input) { inputData = input; }
	InputData* getInputData() { return inputData; }
private:
	InputData* inputData;
};

std::istream& operator>>(std::istream& is, City& city);

