#include "rtpch.h"
#include "Sphere.h"

Sphere::Sphere(const Point3& center, const float& radius, Material* material)
: m_Center(center)
, m_Radius(radius)
, m_Material(material)
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
			record.material = m_Material;
			return true;
		}

		t = (-halfb + std::sqrtf(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.getPosition(t);
			record.normal = (record.p - m_Center) / m_Radius;
			record.material = m_Material;
			return true;
		}
	}

	return false;
}

bool Sphere::getBoundingBox(const float& t0, const float& t1, Bounds3& box) const
{
	box = Bounds3(m_Center - Vector3f(m_Radius), m_Center + Vector3f(m_Radius));
	return true;
}

void Sphere::getUVCoord(const Point3& point, float& u, float& v)
{
	Vector3f p = (point - m_Center) / m_Radius;
	float phi = std::atan2f(p.z(), p.x());
	float theta = std::asinf(p.y());

	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}
