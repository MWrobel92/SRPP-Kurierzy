#pragma once
#include "Solver.h"

class Solver2opt : public Solver {
public:
	Solution* process(InputData* input);
private:
	Route* solveTSP(InputData* input);
};