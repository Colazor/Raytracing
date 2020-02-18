#pragma once
#include "Pixel.h"

class Texture
{
public:
	Texture(const char* texture_path);

	~Texture()
	{
		delete[] m_Data;
		m_Data = nullptr;
	}
	const Pixel* GetData() const { return m_Data; }
	const Color GetData(float u, float v) const 
	{ 

		int xLoc = static_cast<unsigned int>(u * m_Width);
		int yLoc = static_cast<unsigned int>(v * m_Height);

		return m_Data[m_Width * yLoc + xLoc].MakeColor();
	}


	const int GetWidth() const { return m_Width; }
	const int GetHeight() const { return m_Height; }
	const int GetBPP() const { return m_Bpp; }

private:
	int m_Width = 0, m_Height = 0, m_Bpp = 0;
	Pixel* m_Data;
};
