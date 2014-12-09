#pragma once
#include <vector>
class City;

class InputData
{
public:
	InputData(int k, City* warehouse, std::vector<City*> cities);
	~InputData();
	int getK() { return k; }
	City* getWarehouse() { return warehouse; }
	std::vector<City*> getCities() { return cities; }

	//returns distance between two cities
	//indexed as follows: 0=warehouse, 1=cities[0], 2=cities[1], ...
	double getDistance(int i, int j);
	
	//returns city (0=warehouse)
	City* getCity(int i);
private:
	int k;
	City* warehouse;
	std::vector<City*> cities;
	
	std::vector<std::vector<double> > distance;
	void precalculateDistance();
};

