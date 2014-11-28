#include "Solver2opt.h"
#include "PizzaDivider.h"
using namespace std;

Solver2opt::Solver2opt(bool withRotations): withRotations(withRotations) {

}

Solution* Solver2opt::process(InputData* input) {
	PizzaDivider* divider = new PizzaDivider();
	Solution* best = NULL;
	for (int rot = 0; rot < input->getK(); ++rot) {
		vector<InputData*> divided = divider->divide(input, rot);

		vector<Route*> routes;
		for (int i = 0; i < divided.size(); ++i) {
			routes.push_back(solveTSP(divided[i]));
		}

		Solution* solution = new Solution(routes);
		float bestLen = 1e10;
		if (best != NULL) bestLen = best->getLength();

		if (solution->getLength() < bestLen) {
			if (best) delete best;
			best = solution;
		} else {
			delete solution;
		}

		if (!withRotations) break;
	}
	return best;
}

Route* Solver2opt::solveTSP(InputData* input) {
	vector<City*> cities = input->getCities();

	City* warehouse = input->getWarehouse();
	Route* currentRoute = new Route(warehouse);
	for (int i = 0; i < cities.size(); ++i) {
		currentRoute->append(cities[i]);
	}

	bool somethingChanged;
	float bestLength = 1e10;
	do {
		somethingChanged = false;

		int bestI = -1;
		int bestJ = -1;

		for (int i = 1; i < currentRoute->getNumberOfCities(); ++i) {
			for (int j = i + 1; j < currentRoute->getNumberOfCities(); ++j) {
				currentRoute->swapSubroute(i, j);
				float len = currentRoute->getLength();
				if (len < bestLength) {
					bestI = i;
					bestJ = j;
					bestLength = len;
					somethingChanged = true;
				}
				currentRoute->swapSubroute(i, j);
			}
		}
		if (somethingChanged) {
			currentRoute->swapSubroute(bestI, bestJ);
		}
	} while (somethingChanged);

	return currentRoute;
}
