#pragma once
#include "Solver.h"
#include "InputData.h"

class RandomSolver :
	public Solver
{
public:
	RandomSolver();
	~RandomSolver();
	Solution* process(InputData* input);
};

