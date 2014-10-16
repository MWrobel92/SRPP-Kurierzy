#pragma once
#include <string>
#include <allegro.h>

class Solution
{
public:
	Solution();
	~Solution();
	void saveToFile(std::string filename);
	void draw(BITMAP* bmp, int x, int y);
};

