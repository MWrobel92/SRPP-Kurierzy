#include "Solver3opt.h"
#include "PizzaDivider.h"
using namespace std;

Solver3opt::Solver3opt(bool withRotations) : withRotations(withRotations) {

}

Solution* Solver3opt::process(InputData* input) {
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

Route* Solver3opt::solveTSP(InputData* input) {
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
		int bestK = -1;
		int bestM = -1;

		for (int i = 1; i < currentRoute->getNumberOfCities(); ++i) {
			for (int j = i; j < currentRoute->getNumberOfCities(); ++j) {
				for (int k = j + 1; k < currentRoute->getNumberOfCities(); ++k) {
					for (int m = 1; m < 8; ++m) {
						Route* variant = new Route(*currentRoute);
						variant->perform3optSwap(i, j, k, m);

						float len = variant->getLength();
						if (len < bestLength) {
							bestI = i;
							bestJ = j;
							bestK = k;
							bestM = m;
							bestLength = len;
							somethingChanged = true;
						}
						delete variant;
					}
				}
			}
		}
		if (somethingChanged) {
			currentRoute->perform3optSwap(bestI, bestJ, bestK, bestM);
		}
	} while (somethingChanged);

	return currentRoute;
}
