#include "DeviceDirector.h"

namespace Device
{
	DeviceDirector::DeviceDirector(void) : graphics(NULL), app(NULL)
	{

	}

	DeviceDirector::~DeviceDirector(void)
	{
		Destroy();
	}

	void DeviceDirector::Run()
	{
		app->Run();
	}

	void DeviceDirector::Destroy()
	{
		delete graphics;
		graphics = NULL;

		delete app;
		app = NULL;
	}


	Graphics::GraphicsForm* DeviceDirector::GetGraphics()
	{
		return graphics;
	}

	Application::Application* DeviceDirector::GetApplication()
	{
		return app;
	}

	Common::Size<int>& DeviceDirector::GetSize()
	{
		return app->GetSize();
	}

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

	bool DeviceDirector::Initialize(PRESENT_INTERVAL interval, WindowsInitOption &options)
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

}