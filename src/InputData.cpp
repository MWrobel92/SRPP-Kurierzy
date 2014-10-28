#include "InputData.h"


InputData::InputData(int k, City* warehouse, std::vector<City*> cities):
	k(k), warehouse(warehouse), cities(cities) {

}

InputData::~InputData()
{
}

double InputData::getDistance(int i, int j) {
	if (i < 0 || j < 0 || i >= cities.size() + 1 || j >= cities.size() + 1) return 1e10;
	
	if (distance.size() == 0) precalculateDistance();
	
	return distance[i][j];
}

void InputData::precalculateDistance() {
	distance.clear();
	distance.resize(cities.size() + 1);
	for (int i = 0; i < cities.size() + 1; ++i) {
		distance[i].resize(cities.size() + 1);
		for (int j = 0; j < cities.size() + 1; ++j) {
			distance[i][j] = getCity(i)->distanceTo(getCity(j));
		}
	}
}

City* InputData::getCity(int i) {
	if (i < 0 || i >= cities.size() + 1) return NULL;
	if (i == 0) return warehouse;
	return cities[i - 1];
}
