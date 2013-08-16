#pragma once

#include <hash_map>
#include <string>
#include "SingleTon.h"

namespace Rendering
{
	class TagManager : public Utility::SingleTon<TagManager>
	{
	protected:
		std::hash_map<std::string, int> hash;

	public:
		bool AddTag(std::string key, int id);
		inline bool FindTagValue(std::string key, int *outValue);
	};

}