#pragma once
#include "Solver.h"

class Solver2opt : public Solver {
public:
	Solver2opt(bool withRotations);
	Solution* process(InputData* input);
	Route* solveTSP(InputData* input);
private:
	bool withRotations;
};