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
			LightManager(void)
			{
				lights.reserve(MAX_LIGHT);
			}

			~LightManager(void)
			{
				//아마 오브젝트에서 제거할테니까 굳이 신경 안써도 될텐데
				//그런가?
			}

		public:
			bool Intersect(Frustum *frustum, std::vector<Object*> *out)
			{
				bool intersect = false;

				for(vector<LightForm*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
				{
					if( frustum->In( *iter ) )
					{
						out->push_back( *iter );
						intersect = true;
					}
				}

				return intersect;
			}
			bool Intersect(Frustum *frustum, Object* light)
			{
				bool intersect = false;

				for(vector<LightForm*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
				{
					if( frustum->In( *iter ) )
					{
						intersect = true;
						break;
					}
				}

				return intersect;
			}

		public:
			bool AddLight(LightForm* light)
			{
				if(light->IsLight() == false)
					return false;

				lights.push_back(light);
				return true;
			}

			void Delete(LightForm* light, bool remove)
			{
				for(vector<LightForm*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
				{
					if( (*iter) == light )
					{
						if(remove)
							delete (*iter);

						lights.erase(iter);
						return;
					}
				}
			}

			void DeleteAll(bool remove)
			{
				if(remove)
				{
					for(vector<LightForm*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
						Utility::SAFE_DELETE((*iter));
				}

				lights.clear();
			}
		};
	}
}