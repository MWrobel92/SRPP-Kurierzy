#include "BruteforceSolver.h"
#include "Route.h"
#include <vector>
#include <cstdlib>

#include <iostream>
using namespace std;

BruteforceSolver::BruteforceSolver()
{
}


BruteforceSolver::~BruteforceSolver()
{
}

Solution* BruteforceSolver::process(InputData* input) {
	vector<Route*> routes;
	int k = input->getK();
	vector<City*> cities = input->getCities();
	City* warehouse = input->getWarehouse();

	vector<int> permutation;
	for (int i = 0; i < cities.size(); ++i) {
		permutation.push_back(i);
	}
	
	Solution* bestSolution = NULL;
	double bestLength = 1e10;
	do {
		for (int i = 0; i < cities.size();) {
			Route* route = new Route(warehouse);
			for (int j = 0; j < k && i < cities.size(); ++j, ++i) {
				route->append(cities[permutation[i]]);
			}
			routes.push_back(route);
		}
		
		Solution* currentSolution = new Solution(routes);
		double currentLength = currentSolution->getLength();
		
		if (currentLength < bestLength) {
			bestLength = currentLength;
			if (bestSolution) delete bestSolution;
			bestSolution = currentSolution;
		} else {
			delete currentSolution;
		}

		routes.clear();
	} while (nextPermutation(permutation));
	
	return bestSolution;
}

bool BruteforceSolver::nextPermutation(std::vector<int>& perm) {
	//example: we have 1 2 4 6 5 3, we want to get next permutation
	int i;
	//scan from right side, until next number will be less than previous
	for (i = perm.size() - 1; i >= 1; --i) {
		if (perm[i - 1] < perm[i]) break;
	}
	//1 2 4 6 5 3
	//      i
	
	if (i == 0) return false; //permutation is sorted descending, so this is the last permutation

	//from i to the right end, find the smallest number, which is greater than perm[i - 1]
	int minpos = i;
	for (int pos = i; pos < perm.size(); ++pos) {
		if (perm[pos] < perm[minpos] && perm[pos] > perm[i - 1]) minpos = pos;
	}
	//1 2 4 6 5 3
	//      i
	//        ^minpos
	swap(perm[i - 1], perm[minpos]);
	//1 2 5 6 4 3
	//      i
	
	//reverse vector from i to the right end
	for (int j = i, k = perm.size() - 1; j < k; j++, k--) {
		swap(perm[j], perm[k]);
	}
	//1 2 5 3 4 6
	//      i
	return true;
}
