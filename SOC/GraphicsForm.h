#pragma once

#include "Application.h"
#include "Utility.h"
#include "Color.h"

namespace Device
{
	namespace Graphics
	{
		class GraphicsForm
		{
		public:
			enum PRESENT_INTERVAL
			{
				PRESENT_INTERVAL_DEFAULT,
				PRESENT_INTERVAL_IMMEDIATE,
				PRESENT_INTERVAL_VERTICALSYNC
			};

			enum CLEAR_FLAG
			{
				CLEAR_FLAG_TARGET	= 1,
				CLEAR_FLAG_ZBUFFER	= 2,
				CLEAR_FLAG_STENCIL	= 4
			};

			typedef unsigned int clearFlag;

		public:
			GraphicsForm(PRESENT_INTERVAL interval, Application::Application* app)
			{
				//NULL

			}

		public:
			virtual bool Initialize() = 0;

		protected:
			virtual void CalcElapse() = 0;
			virtual void CalculateFPS() = 0;

		public:
			virtual bool Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil) = 0;
		};
	}
}