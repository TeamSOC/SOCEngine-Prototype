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
		DeviceDirector(void) : graphics(NULL), app(NULL) {}
		~DeviceDirector(void)
		{
			Destroy();
		}

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

		bool Initialize(PRESENT_INTERVAL interval, WindowsInitOption &options)
		{
			app = new Application::Windows(options.rect, options.instance, options.name, options.windowMode, options.isChild, options.parentHandle);

			if( app->Initialize() == false)
				return false;

			graphics = new Graphics::DX(interval, app);

			if(graphics->Initialize() == false)
			{
				Destroy();
				return false;
			}

			return true;
		}

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#endif

		void Run()
		{
			app->Run();
		}

		void Destroy()
		{
			delete graphics;
			graphics = NULL;

			delete app;
			app = NULL;
		}

	public:
		Graphics::GraphicsForm* GetGraphics()
		{
			return graphics;
		}
		Application::Application* GetApplication()
		{
			return app;
		}

		Common::Size<int>& GetSize()
		{
			return app->GetSize();
		}
	};

}