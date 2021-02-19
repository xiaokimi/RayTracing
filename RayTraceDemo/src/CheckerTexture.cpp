#include "rtpch.h"
#include "CheckerTexture.h"

CheckerTexture::CheckerTexture(Texture* odd, Texture* even)
: m_OddTexture(odd)
, m_EvenTexture(even)
{

}

CheckerTexture::~CheckerTexture()
{

}

Color CheckerTexture::getColor(const float& u, const float& v, const Point3& point) const
{
	float sines = std::sinf(10 * point.x()) * std::sinf(10 * point.y()) * std::sinf(10 * point.z());
	if (sines < 0.0f)
		return m_OddTexture->getColor(u, v, point);
	else
		return m_EvenTexture->getColor(u, v, point);
}
