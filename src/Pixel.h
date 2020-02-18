#pragma once
#include "Color.h"

class Pixel
{
	using uc = unsigned char;

public:
	Pixel(Color& color) : R(static_cast<uc>(color.R * 255)), G(static_cast<uc>(color.G * 255)), 
	B(static_cast<uc>(color.B * 255)), A(static_cast<uc>(color.A * 255)) {}
	Pixel(uc r, uc g, uc b, uc a) : R(r), G(g), B(b), A(a) {}

	Pixel() : R(0), G(0), B(0), A(0) {}

	// This function should mostly not be run but in case you have to revert the Pixel back into color values it exists
	const Color MakeColor() const { return Color(R * 0.003921568627f, G * 0.003921568627f, B * 0.003921568627f, A * 0.003921568627f); }

private:
	uc R, G, B, A;
};