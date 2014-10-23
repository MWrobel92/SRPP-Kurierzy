#include "Solution.h"
#include <fstream>
#include <iomanip>

using namespace std;

Solution::Solution(std::vector<Route*> routes): routes(routes) {
}


Solution::~Solution()
{
}


double Solution::getLength() {
	double length = 0.0;
	for (int i = 0; i < routes.size(); ++i) {
		length += routes[i]->getLength();
	}
	return length;
}

void Solution::saveToFile(std::string filename) {
	fstream file(filename.c_str(), ios::out | ios::trunc);

	file << setprecision(10) << getLength() << "\n";
	file << routes.size() << "\n";
	for (int i = 0; i < routes.size(); ++i) {
		file << (*routes[i]) << "\n";
	}

	file.close();
}
