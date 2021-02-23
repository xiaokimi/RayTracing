#include "rtpch.h"
#include "ImageTexture.h"

ImageTexture::ImageTexture(const int& width, const int& height, float* srgb)
: m_Width(width)
, m_Height(height)
, m_SRGB(srgb)
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

	return Color(m_SRGB[index], m_SRGB[index + 1], m_SRGB[index + 2]);
}
