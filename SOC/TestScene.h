#pragma once

#include "Scene.h"

using namespace Rendering;

class TestScene : public Scene
{
private:
	Object *camObject;
	Object *meshObject;

	Object *lightObj;
	Object *lightObj2;

public:
	TestScene(void);
	~TestScene(void);

public:
	virtual void OnInitialize();
	virtual void OnUpdate(float dt);
	virtual void OnRenderPreview();
	virtual void OnRenderPost();
	virtual void OnDestroy();
};

