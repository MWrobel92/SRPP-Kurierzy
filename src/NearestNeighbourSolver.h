#pragma once
#include "Solver.h"

class NearestNeighbourSolver : public Solver {
public:
	Solution* process(InputData* input);
private:
	Route* solveTSP(InputData* input);
};