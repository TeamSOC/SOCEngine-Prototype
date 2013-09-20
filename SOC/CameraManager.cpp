#include "CameraManager.h"

using namespace Rendering;

CameraManager::CameraManager() : Container()
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::SetMainCamera(Camera *cam)
{
	objects.insert(objects.begin(), cam);
}

Camera* CameraManager::GetMainCamera()
{
	return (*objects.begin());
}

std::vector<Camera*>::iterator CameraManager::GetIteratorBegin()
{
	return objects.begin();
}

std::vector<Camera*>::iterator CameraManager::GetIteratorEnd()
{
	return objects.end();
}
