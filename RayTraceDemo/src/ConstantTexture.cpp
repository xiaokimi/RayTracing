#include "rtpch.h"
#include "ConstantTexture.h"

ConstantTexture::ConstantTexture(const Color& color)
: m_Color(color)
{

}

ConstantTexture::~ConstantTexture()
{

}

Color ConstantTexture::getColor(const float& u, const float& v, const Point3& point) const
{
	return m_Color;
}
