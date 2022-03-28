#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <SDL.h>
#include "ResourceLoader.h"
#include "ResourceObject.h"
using std::string;
using std::unordered_map;

namespace Framework::Resource
{
	class ResourceLibrary
	{
	private:
		unordered_map<int, ResourceObject*> resourceLibrary;

	public:
		bool Add(ResourceObject* resourceObject);
		bool Remove(int id);
		ResourceObject* Get(int id);
		std::vector<ResourceObject*> Get();
		void Clear(void);

	};
}