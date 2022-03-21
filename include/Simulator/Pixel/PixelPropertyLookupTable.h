#pragma once

#include <vector>
#include <unordered_map>
#include "PixelType.h"
#include "PixelTypeProperty.h"

using std::unordered_map;
using std::vector;

class PixelPropertyLookupTable
{
	unordered_map<PixelType, PixelTypeProperty*> typePropertyTable;
public:
	PixelPropertyLookupTable(void);
	~PixelPropertyLookupTable(void);
	PixelTypeProperty* Get(PixelType type);
	void AddProperty(PixelType type, PixelTypeProperty* prop);
	void ConstructFromFile();		// add this later
};

