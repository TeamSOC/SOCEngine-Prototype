#pragma once

#include <d3dx9math.h>

namespace Rendering
{
	struct Color
	{
	private:
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
		Color GetColor()
		{
			CalculateColor((*this));
			return (*this); 
		}

		D3DXVECTOR4 GetVectorType()
		{
			Color color = GetColor();
			return D3DXVECTOR4(color.r, color.g, color.b, color.a);
		}

	public:
		void SetColor(Color &color)
		{
			r = color.r;
			g = color.g;
			b = color.b;
			a = color.a;
			CalculateColor(*this);
		}

	private:
		void CalculateColor(Color &color);
	};

}