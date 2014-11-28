#pragma once
#include "Solver.h"

class Solver3opt : public Solver {
public:
	Solver3opt(bool withRotations);
	Solution* process(InputData* input);
private:
	Route* solveTSP(InputData* input);
	bool withRotations;
};