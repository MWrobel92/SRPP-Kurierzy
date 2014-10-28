#include "PizzaSolver.h"


PizzaSolver::PizzaSolver() : liczbaOptymalizacji(10)
{
}

PizzaSolver::~PizzaSolver()
{
}

Solution* PizzaSolver::process(InputData* input) {

	int k = input->getK();
	vector<City*> cities = input->getCities();
	warehouse = input->getWarehouse();

	//Sortowanie miast rosnaco wg k¹ta (sortowanie przez proste wstawianie)
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

	Solution* solution = singleProcess(cities, k);
	Solution* newSolution;

	// Obracanie pizzy po kawa³ku
	for (i = 1; i < k; ++i) { // Ma siê wykonaæ k-1 razy
		
		City* temporary = cities[0];
		temporary->angle += 2 * 3.14159; // + 2 * pi

		for (j = 1; j < cities.size(); ++j) {
			cities[j-1] = cities[j];
		}

		cities[j-1] = temporary;
		newSolution = singleProcess(cities, k);

		if (newSolution->getLength() < solution->getLength()) {
			solution = newSolution;
		}
	}

	return solution;
}

Solution* PizzaSolver::singleProcess(vector<City*> cities, int k) {

	int i, j;
	vector<Route*> routes;

	//Podzia³ pizzy na kawa³ki ;-)
	vector<vector<City*> > fragmentedCitiesList;
	for (i = 0; i < cities.size();) {
		vector<City*> part;
		for (j = 0; j < k && i < cities.size(); ++j, ++i) {
			part.push_back(cities[i]);
		}
		fragmentedCitiesList.push_back(part);
	}

	//Posortowanie ka¿dego fragmentu
	for (i = 0; i < fragmentedCitiesList.size(); ++i) {
		routes.push_back(processPart(fragmentedCitiesList[i]));
	}

	return new Solution(routes);

};

Route* PizzaSolver::processPart(vector<City*> partOfCities) {

	Route* route = new Route(warehouse);
	City* temporary;
	int i, j;

	// Jeœli k¹t jest ostry, sortujemy wg innego algorytmu
	if ((partOfCities[partOfCities.size()-1]->angle - partOfCities[0]->angle) < 1.57)
	{
		//Znalezienie indeksu najbardziej odleg³ego elementu
		int max_id = 0;		

		for (i = 1; i < partOfCities.size(); ++i) {
			if (partOfCities[i]->distanceToCenter > partOfCities[max_id]->distanceToCenter) {
				max_id = i;
			}
		}

		//Posortowanie lewej strony listy rosnaco wg odleglosci
		for (i = 1; i < max_id; ++i) {
			temporary = partOfCities[i];
			for (j = i; j > 0; --j) {
				if (partOfCities[j-1]->distanceToCenter < temporary->distanceToCenter) {
					break;
				}
				else {
					partOfCities[j] = partOfCities[j-1];
				}
			}
			partOfCities[j] = temporary;
		}

		//Posortowanie prawej strony listy rosnaco wg odleglosci
		for (i = max_id+2; i < partOfCities.size(); ++i) {
			temporary = partOfCities[i];
			for (j = i; j > max_id+1; --j) {
				if (partOfCities[j-1]->distanceToCenter >= temporary->distanceToCenter) {
					break;
				}
				else {
					partOfCities[j] = partOfCities[j-1];
				}
			}
			partOfCities[j] = temporary;
		}
	}

	// Próba optymalizacji listy poprzez proste zamiany
	bool sthChanged;
	for (i = 0; i < liczbaOptymalizacji; ++i) {		
		sthChanged = optimalizePart(partOfCities);
		if (!sthChanged) {
			break; // Jesli nic siê nie zmieni³o, nie ma sensu d³u¿ej optymalizowaæ
		}
	}

	//Przepisanie wektora do œcie¿ki
	for (i = 0; i < partOfCities.size(); ++i) {
		route->append(partOfCities[i]);
	}

	return route;
};

bool PizzaSolver::optimalizePart(vector<City*> &partOfCities)
{
	int i;
	bool sthChanged = false;
	City* temporary;

	// Próba optymalizacji listy poprzez zamiany s¹siednich wêz³ów miejscami
	for (i = 0; i < partOfCities.size()-1; ++i) {
		
		double d1, d2; // Odleg³oœci obecne
		double a1, a2; // Odleg³oœci alternatywne

		if (i == 0) {
			d1 = partOfCities[0]->distanceToCenter;
			a1 = partOfCities[1]->distanceToCenter;
		}
		else {
			d1 = partOfCities[i]->distanceTo(partOfCities[i-1]);
			a1 = partOfCities[i+1]->distanceTo(partOfCities[i-1]);
		}
				
		if (i == (partOfCities.size()-2)) {
			d2 = partOfCities[i+1]->distanceToCenter;
			a2 = partOfCities[i]->distanceToCenter;
		}
		else {
			d2 = partOfCities[i+1]->distanceTo(partOfCities[i+2]);
			a2 = partOfCities[i]->distanceTo(partOfCities[i+2]);
		}

		if ((a1 + a2) < (d1 + d2)) {
			// Stwierdziliœmy, ¿e zamieniamy
			temporary = partOfCities[i+1];
			partOfCities[i+1] = partOfCities[i];
			partOfCities[i] = temporary;
			sthChanged = true;
		}
		

	}

	return sthChanged;

};