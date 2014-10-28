#include "RandomSolver.h"
#include "Route.h"
#include <vector>
#include <cstdlib>

using namespace std;

RandomSolver::RandomSolver()
{
}


RandomSolver::~RandomSolver()
{
}

Solution* RandomSolver::process(InputData* input) {
	vector<Route*> routes;
	int k = input->getK();
	vector<City*> cities = input->getCities();
	City* warehouse = input->getWarehouse();

	//shuffle cities
	for (int i = 0; i < cities.size() * 10; ++i) {
		int a = rand() % cities.size();
		int b = rand() % cities.size();
		swap(cities[a], cities[b]);
	}

	for (int i = 0; i < cities.size();) {
		Route* route = new Route(warehouse);
		for (int j = 0; j < k && i < cities.size(); ++j, ++i) {
			route->append(cities[i]);
		}
		routes.push_back(route);
	}

	return new Solution(routes);
}
