#include "rtpch.h"
#include "NoiseTexture.h"
#include "PerlinNoise.h"

NoiseTexture::NoiseTexture(const float& scale /*= 1.0f*/)
: m_Scale(scale)
{

}

NoiseTexture::~NoiseTexture()
{

}

Color NoiseTexture::getColor(const float& u, const float& v, const Point3& point) const
{
	//return PerlinNoise::getInstance().getNoise(point * m_Scale);

	return Color(0.5f * (1.0f + std::sinf(m_Scale * point.z() + 10.0f * PerlinNoise::getInstance().getTurb(point))));
}
