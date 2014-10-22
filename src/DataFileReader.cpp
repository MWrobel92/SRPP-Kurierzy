#include "DataFileReader.h"
#include "City.h"
#include <fstream>
#include <vector>

using namespace std;

DataFileReader::DataFileReader(std::string filename)
{
	data = NULL;

	fstream file(filename.c_str(), ios::in);
	if (!file.good()) return;

	int k;
	file >> k;

	City* warehouse = new City(0);
	file >> (*warehouse);

	vector<City*> cities;

	int cityID = 1;
	do {
		City* city = new City(cityID);
		file >> (*city);
		city->setParameters(warehouse);
		if (file.good()) cities.push_back(city);
		++cityID;
	} while (file.good());
	file.close();

	data = new InputData(k, warehouse, cities);
}


DataFileReader::~DataFileReader()
{
}

InputData* DataFileReader::getData() {
	return data;
}
