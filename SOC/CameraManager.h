#pragma once

#include "Container.h"
#include "Camera.h"

namespace Rendering
{
	class CameraManager : public Container<Camera>
	{
	public:
		CameraManager(void);
		~CameraManager(void);

	public:
		void SetMainCamera(Camera* cam);
		Camera* GetMainCamera();

	public:
		std::vector<Camera*>::iterator GetIteratorBegin();
		std::vector<Camera*>::iterator GetIteratorEnd();
	}; 
}