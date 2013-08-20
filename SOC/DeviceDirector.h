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
			Common::Rect<int> &rect;
			HINSTANCE instance;
			const wchar_t* name;
			bool windowMode;
			bool isChild;
			HWND parentHandle;
		};

		bool Initialize(Graphics::GraphicsForm::PRESENT_INTERVAL interval,WindowsInitOption &options)
		{
			app = new Application::Windows(options.rect, options.instance, options.name, options.windowMode, options.isChild, options.parentHandle);
			graphics = new Graphics::DX(interval, app);

			app->Initialize();
			if(graphics->Initialize() == false)
				Destroy();
		}
#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#endif

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