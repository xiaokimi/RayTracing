#include "rtpch.h"
#include "Sphere.h"

Sphere::Sphere(const Point3& center, const float& radius, Matetial* matetial)
: m_Center(center)
, m_Radius(radius)
, m_Matetial(matetial)
{

}

Sphere::~Sphere()
{

}

bool Sphere::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	Vector3f oc = ray.getOrigin() - m_Center;
	float a = dot(ray.getDirection(), ray.getDirection());
	float halfb = dot(ray.getDirection(), oc);
	float c = dot(oc, oc) - m_Radius * m_Radius;
	float discriminant = halfb * halfb - a * c;
	if (discriminant > 0)
	{
		float t = (-halfb - std::sqrtf(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.getPosition(t);
			record.normal = (record.p - m_Center) / m_Radius;
			record.matetial = m_Matetial;
			return true;
		}

		t = (-halfb + std::sqrtf(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.getPosition(t);
			record.normal = (record.p - m_Center) / m_Radius;
			record.matetial = m_Matetial;
			return true;
		}
	}

	return false;
}
