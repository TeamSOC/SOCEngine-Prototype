#pragma once

#include "Rendering.h"
#include "Container.h"
#include "BaseScene.h"

class Scene : public BaseScene, public Container<Rendering::Object>
{
public:
	bool destroyMgr;

protected:
	Device::Graphics::GraphicsForm			*graphics;
	Rendering::Light::LightManager			*lightMgr;
	Rendering::Texture::TextureManager		*textureMgr;
	Rendering::Shader::ShaderManager		*shaderMgr;
	Rendering::CameraManager				*cameraMgr;

public:
	Scene(void);
	~Scene(void);

private:
	virtual void Initialize();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnInitialize() = 0;
	virtual void OnRenderPreview() = 0;
	virtual void OnUpdate(float dt) = 0;
	virtual void OnRenderPost() = 0;
	virtual void OnDestroy() = 0;

public:
	Rendering::Light::LightManager* GetLightManager();
	Rendering::Texture::TextureManager* GetTextureManager();
	Rendering::Shader::ShaderManager* GetShaderManager();
	std::vector<Rendering::Object*>* GetRootObjects();
	Rendering::CameraManager* GetCameraManager();
};