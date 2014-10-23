#pragma once
#include "Solver.h"
#include "InputData.h"
#include "Route.h"
#include <vector>

using namespace std;

class PizzaSolver :
	public Solver
{
public:
	City* warehouse;
	const int liczbaOptymalizacji;

	PizzaSolver();
	~PizzaSolver();
	Solution* process(InputData* input);

private:
	Route* processPart(vector<City*> partOfCities);
	bool optimalizePart(vector<City*> &partOfCities);
};