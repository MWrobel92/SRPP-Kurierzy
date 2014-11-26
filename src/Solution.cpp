#include "Solution.h"
#include <fstream>
#include <iomanip>

using namespace std;

Solution::Solution(std::vector<Route*> routes): routes(routes) {
}

Solution::Solution(const Solution &old) {
	
	int n = old.routes.size();
	for (int i=0; i<n; ++i) {
		routes.push_back(new Route(*old.routes.at(i)));
	}

}

Solution::~Solution() {
	
	int n = routes.size();
	for (int i=0; i<n; ++i) {
		delete routes.at(i);
	}

}

double Solution::getLength() {
	double length = 0.0;
	for (int i = 0; i < routes.size(); ++i) {
		length += routes[i]->getLength();
	}
	return length;
}

void Solution::saveToFile(std::string filename) {
	fstream file(filename.c_str(), ios::out | ios::trunc);

	file << setprecision(10) << getLength() << "\n";
	file << routes.size() << "\n";
	for (int i = 0; i < routes.size(); ++i) {
		file << (*routes[i]) << "\n";
	}

	file.close();
}

void Solution::mutate () {

	// Losowanie miast
	int pathCount = routes.size();
	int firstPathId = rand()%pathCount;
	int secondPathId = (firstPathId + 1 + rand()%(pathCount-1))%pathCount; // Tak.
	int firstCityId = rand()%routes.at(firstPathId)->getNumberOfCities();
	int secondCityId = rand()%routes.at(secondPathId)->getNumberOfCities();

	// Zamiana miast miejscami
	City* temporary = routes.at(firstPathId)->getCityAt(firstCityId);
	routes.at(firstPathId)->setCityAt(routes.at(secondPathId)->getCityAt(secondCityId), firstCityId);
	routes.at(secondPathId)->setCityAt(temporary, secondCityId);
	
}

void Solution::mutateSoftly () {
	// Losuje miasto i wstawia je w inne miejsce w obrêbie TEJ SAMEJ œcie¿ki

	// Losowanie œcie¿ki
	int pathCount = routes.size();
	int pathId = rand()%pathCount;
	Route* routeToMutate = routes.at(pathId);

	// Przestawienie miasta
	int numberOfCities = routeToMutate->getNumberOfCities();
	int position = rand()%numberOfCities;
	int newPosition = rand()%numberOfCities;
	routeToMutate->moveCity(rand()%numberOfCities, rand()%numberOfCities);
	
	
}