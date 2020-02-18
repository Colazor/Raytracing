#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const char* path)
{
	uint8_t* read_data = stbi_load(path, &m_Width, &m_Height, &m_Bpp, 3);
	m_Data = new Pixel[m_Width * m_Height];
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			m_Data[y * m_Width + x] = Pixel(read_data[(y * m_Width + x) * m_Bpp], read_data[(y * m_Width + x) * m_Bpp + 1], read_data[(y * m_Width + x) * m_Bpp + 2], static_cast<unsigned char>(255));
		}
	}
}
