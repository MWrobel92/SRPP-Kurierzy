#pragma once
#include <vector>
#include "InputData.h"
#include "City.h"

class PizzaDivider {
public:
	PizzaDivider();
	~PizzaDivider();
	std::vector<InputData*> divide(InputData* input, int shift);
};