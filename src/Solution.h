#pragma once
#include <string>
#include <vector>
#include "Route.h"

class Solution
{
public:
	Solution(std::vector<Route*> routes);
	~Solution();
	void saveToFile(std::string filename);
	double getLength();

private:
	std::vector<Route*> routes;
};

