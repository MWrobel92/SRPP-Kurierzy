#pragma once
#include <string>
#include <vector>
//#include <allegro.h>
#include "Route.h"

class Solution
{
public:
	Solution(std::vector<Route*> routes);
	~Solution();
	void saveToFile(std::string filename);
	//void draw(BITMAP* bmp, int x, int y);
	double getLength();
private:
	std::vector<Route*> routes;
};

