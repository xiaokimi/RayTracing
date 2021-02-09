#include "rtpch.h"
#include "Ray.h"

Ray::Ray()
: m_Orig(0.0f, 0.0f, 0.0f)
, m_Dir(0.0f, 0.0f, 0.0f)
{

}

Ray::Ray(const Point3& orig, const Vector3f& dir)
: m_Orig(orig)
, m_Dir(dir)
{

}

Ray::~Ray()
{

}

Point3 Ray::getOrigin() const
{
	return m_Orig;
}

Vector3f Ray::getDirection() const
{
	return m_Dir;
}

Point3 Ray::at(const float& t) const
{
	return m_Orig + m_Dir * t;
}
