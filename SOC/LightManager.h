#pragma once

#include "LightForm.h"
#include "Utility.h"
#include "Frustum.h"

#define MAX_LIGHT 8

using namespace std;

namespace Rendering
{
	namespace Light
	{
		class LightManager
		{
		private:
			std::vector<LightForm*> lights;

		public:
			LightManager(void);
			~LightManager(void);

		public:
			bool Intersect(Frustum *frustum, std::vector<Object*> *out);
			bool Intersect(Frustum *frustum, Object* light);

		public:
			bool AddLight(LightForm* light);
			void Delete(LightForm* light, bool remove);
			void DeleteAll(bool remove);
		};
	}
}