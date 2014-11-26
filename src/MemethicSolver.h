#pragma once
#include "PizzaSolver.h"
#include "InputData.h"
#include "Route.h"
#include <vector>

class MemethicSolver : public Solver
{
public:
	
	MemethicSolver();
	~MemethicSolver();
	Solution* process(InputData* input);

	// Parametry algorytmu memetycznego - s� ustawiane domy�lne, ale mozna te� je zmienia�
	int generations;
	int softMutations;
	int hardMutations;
	int crossbreedings;

private:

	unsigned int bestSolutionLength;

	Solution* findBestSolution(vector<Solution*> &solutions);
	Solution*  generation(vector<Solution*> &solutions);
};