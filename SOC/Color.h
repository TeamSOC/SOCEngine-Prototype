#pragma once

namespace Rendering
{
	struct Color
	{
	public:
		float a;
		float b;
		float g;
		float r;

	public:
		Color();
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);

	public:
		Color operator -(Color c);
		bool operator !=(Color c);
		Color operator *(Color c);
		Color operator *(float f);
		Color operator /(float f);
		Color operator +(Color c);
		bool operator ==(Color c);

	public:
		static Color black();
		static Color blue();
		static Color clear();
		static Color cyan();

		static Color gray();

		float grayscale();

		static Color green();		
		static Color magenta();		
		static Color red();		
		static Color white();		
		static Color yellow();

		static Color Lerp(Color a, Color b, float t);

	public:
		Color& GetColor();

	public:
		void SetColor(Color &color);

	private:
		void CalculateColor(Color *color);
	};

}