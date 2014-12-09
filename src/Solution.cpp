#include "Solution.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>

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

	//	int secondPathId = (firstPathId + 1 + rand() % (pathCount - 1)) % pathCount; // Tak.
	//inna mutacja: zamiana miast z dw�ch s�siednich �cie�ek
	int secondPathId = (firstPathId + 1) % pathCount;
	int firstCityId = rand() % (routes.at(firstPathId)->getNumberOfCities() - 1) + 1;
	int secondCityId = rand()%(routes.at(secondPathId)->getNumberOfCities()-1)+1;

	// Zamiana miast miejscami
	City* temporary = routes.at(firstPathId)->getCityAt(firstCityId);
	routes.at(firstPathId)->setCityAt(routes.at(secondPathId)->getCityAt(secondCityId), firstCityId);
	routes.at(secondPathId)->setCityAt(temporary, secondCityId);

	
}

void Solution::mutateSoftly () {
	// Losuje miasto i wstawia je w inne miejsce w obr�bie TEJ SAMEJ �cie�ki

	// Losowanie �cie�ki
	int pathCount = routes.size();
	int pathId = rand()%pathCount;
	Route* routeToMutate = routes.at(pathId);

	// Przestawienie miasta
	int numberOfCities = routeToMutate->getNumberOfCities();
	int position = (rand()%(numberOfCities-1))+1;
	int newPosition = (rand()%(numberOfCities-1))+1;
	routeToMutate->moveCity(position, newPosition);
	
	
}

void Solution::crossbreedWith(Route* newRoute, int maxLength) {

	// Sprawdzenie, w kt�rej �cie�ce jest ile punkt�w ze starej �cie�ki
	vector<vector<City*> > commonCities;
	int i, j, k;
	for (i=0; i<routes.size(); ++i) {
		vector<City*> newVector;
		for(j=1; j<newRoute->getNumberOfCities(); ++j) { // 1 - �eby nie bra� magazynu
			for(k=1; k<routes.at(i)->getNumberOfCities(); ++k) { // 1 - �eby nie bra� magazynu
				if (*newRoute->getCityAt(j) == *routes.at(i)->getCityAt(k)) {
					newVector.push_back(newRoute->getCityAt(j));
					break;
				}
			}
		}
		commonCities.push_back(newVector);
	}

	// Wybranie �cie�ki o najwi�kszej liczbie wsp�lnych punkt�w
	int oldPathId = 0;
	for (i=1; i<commonCities.size(); ++i) {
		if (commonCities.at(i).size() > commonCities.at(oldPathId).size()) {
			oldPathId = commonCities.at(i).size();
			oldPathId = i;
		}
	}

	// Zamiana �cie�ek miejscami
	Route* oldRoute = routes.at(oldPathId);
	routes.at(oldPathId) = newRoute;

	// Wyszukanie miast, kt�re nale�a�y do starej �cie�ki, a nie nale�� do nowej
	vector<City*> lonelyCities;
	for (i=1; i<oldRoute->getNumberOfCities(); ++i) { // 1 - �eby nie bra� magazynu
		bool is = false;
		for (j=1; j<newRoute->getNumberOfCities(); ++j) { // 1 - �eby nie bra� magazynu
			if(*oldRoute->getCityAt(i) == *newRoute->getCityAt(j)) {
				is = true;
				break;
			}
		}
		if (!is) {
			lonelyCities.push_back(oldRoute->getCityAt(i));
		}
	}

	// Zast�pienie miast, kt�re zosta�y zdublowane
	for (i=0; i<commonCities.size(); ++i) {

		if (i == oldPathId) {
			continue;
		}

		for (j=0; j<commonCities.at(i).size(); ++j) {

			
			for (k=0; k<routes.at(i)->getNumberOfCities(); ++k) {
				if (*commonCities.at(i).at(j) == *routes.at(i)->getCityAt(k)){
					break;
				}
			}

			// i - indeks �cie�ki ; k - indeks punktu

			if (lonelyCities.size() > 0) {
				// Zast�pienie miasta kt�rym� samotnym
				City* temp = lonelyCities.at(lonelyCities.size()-1);
				lonelyCities.pop_back();
				routes.at(i)->setCityAt(temp, k);
			}
			else {
				// Wyci�cie miasta
				routes.at(i)->removeCityAt(k);
			}
		}
	}

	// Wsadzenie gdzie� pozosta�ych samotnych miast
	for (i=lonelyCities.size(); i>0; --i) {
		City* temp = lonelyCities.at(i-1);
		lonelyCities.pop_back();

		for (j=0; j<routes.size(); ++j) {
			if ((j != oldPathId) &&(routes.at(j)->getNumberOfCities() < maxLength)) {
				routes.at(j)->append(temp);
				break;
			}
		}
	}

}

Solution* Solution::crossbreed(Solution* secondSol, int maxLength) {
	
	Solution* newSolution = new Solution(*secondSol);

	// Wybranie �cie�ki do przeniesienia w ca�o�ci
	Route* routeToMove = new Route(*routes.at(rand()%routes.size()));
	newSolution->crossbreedWith(routeToMove, maxLength);	

	return newSolution;
}

int Solution::getRouteCount() {
	return routes.size();
}
InputData* Solution::getRouteAsInputData(int i) {
	return new InputData(routes[0]->getNumberOfCities(),
		routes[0]->getCityAt(0), routes[i]->getCities()); //FIXME
}
