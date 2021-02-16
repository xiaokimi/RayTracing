#include "rtpch.h"
#include "Ray.h"

Ray::Ray(const Point3& orig, const Vector3f& dir)
: m_Origin(orig)
, m_Direction(dir)
{

}

Ray::~Ray()
{

}

Point3 Ray::getOrigin() const
{
	return m_Origin;
}

Vector3f Ray::getDirection() const
{
	return m_Direction;
}

Point3 Ray::getPosition(const float& t) const
{
	return m_Origin + m_Direction * t;
}
