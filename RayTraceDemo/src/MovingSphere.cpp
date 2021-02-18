#include "rtpch.h"
#include "MovingSphere.h"

MovingSphere::MovingSphere(const Point3& center0, const Point3& center1, const float& t0, const float& t1, const float& radius, Material* material)
: m_Center0(center0)
, m_Center1(center1)
, m_Time0(t0)
, m_Time1(t1)
, m_Radius(radius)
, m_Material(material)
{

}

MovingSphere::~MovingSphere()
{

}

bool MovingSphere::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	Vector3f center = getCenter(ray.getTime());
	Vector3f oc = ray.getOrigin() - center;
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
			record.normal = (record.p - center) / m_Radius;
			record.material = m_Material;
			return true;
		}

		t = (-halfb + std::sqrtf(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.getPosition(t);
			record.normal = (record.p - center) / m_Radius;
			record.material = m_Material;
			return true;
		}
	}

	return false;
}


bool MovingSphere::getBoundingBox(const float& t0, const float& t1, Bounds3& box) const
{

	return true;
}

Point3 MovingSphere::getCenter(const float& time) const
{
	return m_Center0 + (time - m_Time0) / (m_Time1 - m_Time0) * (m_Center1 - m_Center0);
}
