#pragma once
#include "Solver.h"

class Solver2opt : public Solver {
public:
	Solver2opt(bool withRotations);
	Solution* process(InputData* input);
private:
	Route* solveTSP(InputData* input);
	bool withRotations;
};