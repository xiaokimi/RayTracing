#include "rtpch.h"
#include "Sphere.h"

Sphere::Sphere()
: m_Center(0.0f, 0.0f, 0.0f)
, m_Radius(0.0f)
, m_Material(nullptr)
{

}

Sphere::Sphere(const Point3& center, const float& radius, Material* material)
: m_Center(center)
, m_Radius(radius)
, m_Material(material)
{

}

Sphere::~Sphere()
{

}

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	Vector3f oc = ray.getOrigin() - m_Center;
	float a = ray.getDirection().dot(ray.getDirection());
	float halfb = ray.getDirection().dot(oc);
	float c = oc.dot(oc) - m_Radius * m_Radius;
	float discriminant = halfb * halfb - a * c;
	if (discriminant > 0)
	{
		float t = (-halfb - std::sqrt(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.at(t);
			record.normal = (record.p - m_Center) / m_Radius;
			record.material = m_Material;
			return true;
		}

		t = (-halfb + std::sqrt(discriminant)) / a;
		if (t > tMin && t < tMax)
		{
			record.t = t;
			record.p = ray.at(t);
			record.normal = (record.p - m_Center) / m_Radius;
			record.material = m_Material;
			return true;
		}
	}
	
	return false;
}
