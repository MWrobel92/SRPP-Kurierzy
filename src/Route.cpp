#include "Route.h"


Route::Route(City* startingCity) {
	route.push_back(startingCity);
}

Route::Route(const Route& old) {
	route = old.route;
}

Route::~Route()
{
}

void Route::append(City* city) {
	route.push_back(city);
}

void Route::removeLast() {
	route.erase(route.end() - 1);
}

double Route::getLength() {
	double length = 0.0;
	int prev = route.size() - 1;

	InputData* input = route[0]->getInputData(); //for precalculated distance

	for (int i = 0; i < route.size(); ++i) {
//		length += route[i]->distanceTo(route[prev]);
		length += input->getDistance(route[i]->id, route[prev]->id); //FIXME
		prev = i;
	}
	return length;
}

double Route::getPartialLength() {
	double length = 0.0;
	for (int i = 0; i < route.size() - 1; ++i) {
		length += route[i]->distanceTo(route[i + 1]);
	}
	return length;
}

int Route::getNumberOfCities() {
	return route.size();
}

City* Route::getCityAt(int id) {
	return route.at(id);
};

void Route::setCityAt(City* toSet, int id) {
	route.at(id) = toSet;
};

void Route::removeCityAt(int id) {
	for (int i=id; i<route.size()-1; ++i) {
		route.at(i) = route.at(i+1);
	}
	route.pop_back();
}

void Route::moveCity(int position, int newPosition){
	//Przestawia miasta z pierwszej pozycji na drug¹

	int i;
	City* temporary = route.at(position);
	
	if (newPosition > position) {

		for (i=position; i<newPosition; ++i) {
			route.at(i) = route.at(i+1);
		}

	}
	else {

		for (i=position; i>newPosition; --i) {
			route.at(i) = route.at(i-1);
		}
	}

	route.at(i) = temporary;
};

void Route::swapSubroute(int i, int j) {
	while (i < j) {
		City* tmp = route[i];
		route[i] = route[j];
		route[j] = tmp;

		++i;
		--j;
	}
}

void Route::perform3optSwap(int i, int j, int k, int m) {
	bool swapPieces = (m & 0x4);
	bool swapLeft = (m & 0x2);
	bool swapRight = (m & 0x1);
	if (swapPieces) swapSubroute(i, k);
	if (swapLeft)   swapSubroute(i, j);
	if (swapRight)  swapSubroute(j + 1, k);
}

std::vector<City*> Route::getCities() {
	return route;
}

std::ostream& operator<<(std::ostream& os, Route& route) {
	for (int i = 0; i < route.route.size(); ++i) {
		os << route.route[i]->id << ' ';
	}
	os << '0';
	return os;
}

