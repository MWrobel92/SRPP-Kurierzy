#pragma once
#include "InputData.h"

class DataSource
{
public:
	DataSource();
	virtual ~DataSource();
	virtual InputData* getData() = 0;
};

