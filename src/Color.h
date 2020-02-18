#pragma once
#include "Utils.h"

class Color
{
public:
	Color() : R(0.f), G(0.f), B(0.f), A(1.0f) {}
	explicit Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) 
	{
		R = fmin(R, 1.0f);
		G = fmin(G, 1.0f);
		B = fmin(B, 1.0f);
		A = fmin(A, 1.0f);
	}

	~Color() {}
	float R, G, B, A;

	Color operator+ (const Color& Other) const 
	{ 
		return Color(R + Other.R, G + Other.G, B + Other.B, A + Other.A);
	}
	Color operator* (const float d) const { return Color(R * d, G * d, B * d, A * d); }
	Color operator* (const Color& Other) const
	{
		return Color(R * Other.R, G * Other.G, B * Other.B, A * Other.A);
	}
	Color operator/ (const float d) const
	{
		return Color(R / d, G / d, B / d, A / d);
	}
	Color average(const Color& Other) const
	{
		return Color((R + Other.R) * 0.5f, (G + Other.G) * 0.5f, (B + Other.B) * 0.5f, (A + Other.A) * 0.5f);
	}
	
private:
};
