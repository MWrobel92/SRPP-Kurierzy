#include "NearestNeighbourSolver.h"
#include "PizzaDivider.h"
using namespace std;

Solution* NearestNeighbourSolver::process(InputData* input) {
	PizzaDivider* divider = new PizzaDivider();
	vector<InputData*> divided = divider->divide(input, 0);

	vector<Route*> routes;
	for (int i = 0; i < divided.size(); ++i) {
		routes.push_back(solveTSP(divided[i]));
	}
	return new Solution(routes);
}

Route* NearestNeighbourSolver::solveTSP(InputData* input) {
	vector<City*> cities = input->getCities();

	City* warehouse = input->getWarehouse();
	Route* currentRoute = new Route(warehouse);
	
	while (cities.size() > 0) {
		int bestIndex = -1;
		float bestLength = 1e10;
		for (int i = 0; i < cities.size(); ++i) {
			currentRoute->append(cities[i]);	
			float length = currentRoute->getPartialLength();
			if (length < bestLength) {
				bestIndex = i;
				bestLength = length;
			}
			currentRoute->removeLast();
		}

		currentRoute->append(cities[bestIndex]);
		cities.erase(cities.begin() + bestIndex);
	}
	
	return currentRoute;
}
