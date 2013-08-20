#pragma once

#include "TagManager.h"

namespace Rendering
{
	class LayerManager : protected TagManager
	{

	public:
		bool AddLayer(std::string key, int id)
		{
			return TagManager::AddTag(key, id);
		}

		inline bool FindLayerValue(std::string key, int *outValue)
		{
			return TagManager::FindTagValue(key, outValue);
		}
	};

}