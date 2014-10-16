#include "DataFileReader.h"


DataFileReader::DataFileReader(std::string filename)
{
}


DataFileReader::~DataFileReader()
{
}

InputData* DataFileReader::getData() {
	return new InputData(); //FIXME
}
