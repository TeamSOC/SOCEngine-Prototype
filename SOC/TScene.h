#pragma once

#include "LightManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Light.h"
#include "Camera.h"

using namespace Rendering;

class TestScene
{
private:
	Light::LightManager *lightMgr;
	Texture::TextureManager *textureMgr;
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
		textureMgr = new Texture::TextureManager();
		shaderMgr = new Shader::ShaderManager();
		cam = new Camera(0,0);

		test->Init(shaderMgr);

		cam->SetPosition(SOC_Vector3(0, 0, 2.0f));
		cam->LookAt(SOC_Vector3(0, 0, -5));
	}

	void loop()
	{
		Device::Graphics::GraphicsForm *graphics = Device::DeviceDirector::GetInstance()->GetGraphics();

		Device::Graphics::GraphicsForm::clearFlag flags = Device::Graphics::GraphicsForm::CLEAR_FLAG_TARGET | Device::Graphics::GraphicsForm::CLEAR_FLAG_ZBUFFER;
		graphics->Clear(flags, Color::blue());

		bool b;
		b = graphics->BeginScene();
		{
			SOC_Matrix viewMat;
			SOC_Matrix projectionMat;
			cam->GetViewMatrix(&viewMat);
			cam->GetPerspectiveMatrix(&projectionMat, 0);

			test->SetMat(&viewMat, &projectionMat);
			test->Render(0, NULL);
		}
		b = graphics->EndScene();

		graphics->Present();
	}


};

