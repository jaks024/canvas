#pragma once
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include "ResourceLoader.h"
#include "ResourceObject.h"
using std::string;
using std::map;

namespace Framework::Resource
{
	class ResourceLibrary
	{
	private:
		map<string, ResourceObject*> resourceLibrary;

	public:
		bool Add(ResourceObject* resourceObject);
		bool Remove(string id);
		ResourceObject* Get(string id);
		std::vector<ResourceObject*> Get();
		void Clear(void);

	};
}