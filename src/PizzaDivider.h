#pragma once
#include <vector>
#include "InputData.h"

class PizzaDivider {
public:
	PizzaDivider();
	~PizzaDivider();
	std::vector<InputData*> divide(InputData* input, int shift);
};