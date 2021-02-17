#include "rtpch.h"
#include "Ray.h"

Ray::Ray(const Point3& orig, const Vector3f& dir, const float& time /*= 0.0f*/)
: m_Origin(orig)
, m_Direction(dir)
, m_Time(time)
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

float Ray::getTime() const
{
	return m_Time;
}

Point3 Ray::getPosition(const float& t) const
{
	return m_Origin + m_Direction * t;
}
