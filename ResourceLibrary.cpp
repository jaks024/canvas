#include "ResourceLibrary.h"

bool ResourceLibrary::Add(ResourceObject* resourceObject)
{
	auto const &result = resourceLibrary.try_emplace(resourceObject->id, resourceObject);
	return result.second;
}

bool ResourceLibrary::Remove(string id)
{
	ResourceObject* resObj = Get(id);
	if (resObj != nullptr) {
		resourceLibrary.erase(id);
		delete(resObj);
		return true;
	}
	return false;
}

ResourceObject* ResourceLibrary::Get(string id)
{
	auto result = resourceLibrary.find(id);
	if (result != resourceLibrary.end()) {
		return result->second;
	} 
	return nullptr;
}

std::vector<ResourceObject*> ResourceLibrary::Get()
{
	std::vector<ResourceObject*> values;
	for (std::map<string, ResourceObject*>::iterator it = resourceLibrary.begin(); it != resourceLibrary.end(); ++it) {
		values.push_back(it->second);
	}
	return values;
}

void ResourceLibrary::Clear(void)
{
	for (std::map<string, ResourceObject*>::iterator it = resourceLibrary.begin(); it != resourceLibrary.end(); ++it) {
		delete(it->second);
		printf("Freed: %s", it->second->id.c_str());
	}
	resourceLibrary.clear();
	printf("All resources cleared");
}
