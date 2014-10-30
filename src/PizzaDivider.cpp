#include "PizzaDivider.h"

using namespace std;

PizzaDivider::PizzaDivider() {
}

PizzaDivider::~PizzaDivider() {
}

std::vector<InputData*> PizzaDivider::divide(InputData* input, int shift) {
	int k = input->getK();
	vector<City*> cities = input->getCities();
	City* warehouse = input->getWarehouse();

	//Sortowanie miast rosnaco wg kąta (sortowanie przez proste wstawianie)
	int i, j;
	City* temporary;
	for (i = 1; i < cities.size(); ++i) {
		temporary = cities[i];
		for (j = i; j > 0; --j) {
			if (cities[j-1]->angle < temporary->angle) {
				break;
			}
			else {
				cities[j] = cities[j-1];
			}
		}
		cities[j] = temporary;
	}

	// Obracanie pizzy po kawałku
	for (i = 0; i < shift; ++i) {
		City* temporary = cities[0];
		temporary->angle += 2 * 3.14159; // + 2 * pi

		for (j = 1; j < cities.size(); ++j) {
			cities[j-1] = cities[j];
		}

		cities[j-1] = temporary;
	}
	
	//Podział pizzy na kawałki ;-)
	vector<InputData*> divided;
//	vector<vector<City*> > fragmentedCitiesList;
	for (i = 0; i < cities.size();) {
		vector<City*> part;
		for (j = 0; j < k && i < cities.size(); ++j, ++i) {
			part.push_back(cities[i]);
		}
		divided.push_back(new InputData(k, warehouse, part));
		
//		fragmentedCitiesList.push_back(part);
	}

	return divided;
}