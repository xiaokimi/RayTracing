#include "rtpch.h"
#include "NoiseTexture.h"
#include "PerlinNoise.h"

NoiseTexture::NoiseTexture()
{

}

NoiseTexture::~NoiseTexture()
{

}

Color NoiseTexture::getColor(const float& u, const float& v, const Point3& point) const
{
	return PerlinNoise::getInstance().getNoise(point);
}
