#include "../../../include/Framework/Resource/ResourceLibrary.h"

namespace Framework::Resource
{
	bool ResourceLibrary::Add(ResourceObject* resourceObject)
	{
		auto const& result = resourceLibrary.try_emplace(resourceObject->id, resourceObject);
		return result.second;
	}

	bool ResourceLibrary::Remove(int id)
	{
		ResourceObject* resObj = Get(id);
		if (resObj != nullptr) {
			resourceLibrary.erase(id);
			delete(resObj);
			return true;
		}
		return false;
	}

	ResourceObject* ResourceLibrary::Get(int id)
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
		for (auto& [key, resObj] : resourceLibrary)
		{
			values.emplace_back(resObj);;
		}
		return values;
	}

	void ResourceLibrary::Clear(void)
	{
		for (auto& [key, resObj] : resourceLibrary)
		{
			printf("Freed: %d", resObj->id);
			delete(resObj);
		}
		resourceLibrary.clear();
		printf("All resources cleared");
	}

}