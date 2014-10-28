#pragma once
#include "Solver.h"
#include "InputData.h"

//It only checks routes with maximum length (k). So, if n=100 and k=5,
//all checked routes will pass through 5 cities.
class BruteforceSolver :
	public Solver
{
public:
	BruteforceSolver();
	~BruteforceSolver();
	Solution* process(InputData* input);
private:
	bool nextPermutation(std::vector<int>& perm);
};

