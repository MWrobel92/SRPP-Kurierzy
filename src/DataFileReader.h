#pragma once
#include "DataSource.h"
#include <string>

class DataFileReader :
	public DataSource
{
public:
	DataFileReader(std::string filename);
	~DataFileReader();
	InputData* getData();

private:
	InputData* data;
};

