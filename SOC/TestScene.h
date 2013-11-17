#pragma once

#include "Scene.h"

using namespace Rendering;

class TestScene : public Scene
{
private:
	Object *camObject;
	Object *meshObject;
	Object *meshObject2;

	Object *lightObj;
	Object *lightObj2;

private:
	LPD3DXMESH gpSphere;
	LPD3DXEFFECT ls;

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

