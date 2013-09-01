#pragma once

#include "LightManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Light.h"
#include "Test.h"
#include "Camera.h"

using namespace Rendering;

class TestScene
{
private:
	Light::LightManager *lightMgr;
	TextureManager *textureMgr;
	Shader::ShaderManager *shaderMgr;
	Camera *cam;
	std::vector<Object*> rootObjects;

private:
	Test *test;

public:
	TestScene(void)
	{
	}

	~TestScene(void)
	{
	}

public:
	void init()
	{
		test = new Test();
		rootObjects.push_back( test );

		lightMgr = new Light::LightManager();
		textureMgr = new TextureManager();
		shaderMgr = new Shader::ShaderManager();
		cam = new Camera(Device::DeviceDirector::GetInstance(), NULL, &rootObjects, lightMgr, NULL);

		test->Init(shaderMgr);
	}

	void loop()
	{
		test->Render(NULL);
	}


};

