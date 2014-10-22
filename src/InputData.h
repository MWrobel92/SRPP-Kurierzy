#pragma once
#include <vector>
#include "City.h"

class InputData
{
public:
	InputData(int k, City* warehouse, std::vector<City*> cities);
	~InputData();
	int getK() { return k; }
	City* getWarehouse() { return warehouse; }
	std::vector<City*> getCities() { return cities; }
private:
	int k;
	City* warehouse;
	std::vector<City*> cities;
};

