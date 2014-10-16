#pragma once
#include "Solution.h"
#include "InputData.h"

class Solver
{
public:
	Solver();
	virtual ~Solver();
	virtual Solution* process(InputData* input) = 0;
};

