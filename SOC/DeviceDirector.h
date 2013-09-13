#pragma once

#include "Platform.h"
#include "SingleTon.h"
#include "Rect.h"
#include "Color.h"
#include "BaseScene.h"

namespace Device
{
	class DeviceDirector : public Utility::SingleTon<DeviceDirector>
	{
	private:
		float elapse;
		float  fps;	

	private:
		Graphics::GraphicsForm *graphics;
		Application::Application *app;
		BaseScene* scene;
		BaseScene* nextScene;

	public:
		DeviceDirector(void);
		~DeviceDirector(void);

	private:
		void CalculateElapse();
		void CalculateFPS();

	public:
#if defined(WIN32) && !defined(_USE_GL_DEFINES)
		struct WindowsInitOption
		{
			Common::Rect<int> rect;
			HINSTANCE instance;
			const char* name;
			bool windowMode;
			bool isChild;
			HWND parentHandle;

			WindowsInitOption(HINSTANCE hInst);
			WindowsInitOption(Common::Rect<int> rect, HINSTANCE instance, const char* name, bool windowMode, bool isChild, HWND parentHandle);
		};
		bool Initialize(PRESENT_INTERVAL interval, WindowsInitOption &options);

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#endif

		void Run();
		void Destroy();

	public:
		Graphics::GraphicsForm* GetGraphics();
		Application::Application* GetApplication();

		Common::Size<int>& GetSize();

		void SetScene(BaseScene* scene);
		void SetNextScene(BaseScene *scene);

		BaseScene* GetScene();
	};
}