#include "rtpch.h"
#include "ImageTexture.h"

ImageTexture::ImageTexture(const int& width, const int& height, unsigned char* pixels)
: m_Width(width)
, m_Height(height)
, m_Data(pixels)
{

}

ImageTexture::~ImageTexture()
{

}

Color ImageTexture::getColor(const float& u, const float& v, const Point3& point) const
{
	int i = ((int)(u * m_Width) % m_Width + m_Width) % m_Width;
	int j = ((int)((1.0f - v) * m_Height) % m_Height + m_Height) % m_Height;
	int index = (j * m_Width + i) * 3;

	float r = std::powf(m_Data[index] / 255.0f, M_GAMMA);
	float g = std::powf(m_Data[index + 1] / 255.0f, M_GAMMA);
	float b = std::powf(m_Data[index + 2] / 255.0f, M_GAMMA);

	return Color(r, g, b);
}
