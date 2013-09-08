#pragma once

#include "Rendering.h"
#include "SingleTon.h"
#include "Rect.h"
#include "Color.h"

namespace Device
{
	class DeviceDirector : public Utility::SingleTon<DeviceDirector>
	{
	private:
		Graphics::GraphicsForm *graphics;
		Application::Application *app;

	public:
		DeviceDirector(void);
		~DeviceDirector(void);

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

			WindowsInitOption(HINSTANCE hInst)
			{
				rect = Common::Rect<int>(0, 0, 800, 800);
				instance = hInst;
				name = "TEST";
				windowMode = true;
				isChild = false;
				parentHandle = NULL;
			}

			WindowsInitOption(Common::Rect<int> rect, HINSTANCE instance, const char* name, bool windowMode, bool isChild, HWND parentHandle)
			{
				this->rect = rect;
				this->instance = instance;
				this->name = name;
				this->windowMode = windowMode;
				this->isChild = isChild;
				this->parentHandle = parentHandle;
			}
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
	};
}