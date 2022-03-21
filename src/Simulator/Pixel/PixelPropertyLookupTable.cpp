#include "../../../include/Simulator/Pixel/PixelPropertyLookupTable.h"

PixelPropertyLookupTable::PixelPropertyLookupTable(void) 
{

}

PixelPropertyLookupTable::~PixelPropertyLookupTable(void)
{
	for (auto& prop : typePropertyTable)
	{
		delete(prop.second);
	}
}

PixelTypeProperty* PixelPropertyLookupTable::Get(PixelType type)
{
	auto result = typePropertyTable.find(type);
	return result == typePropertyTable.end() ? nullptr : result->second;
}

void PixelPropertyLookupTable::AddProperty(PixelType type, PixelTypeProperty* prop)
{
	typePropertyTable.emplace(type, prop);
}

void PixelPropertyLookupTable::ConstructFromFile()
{

}
