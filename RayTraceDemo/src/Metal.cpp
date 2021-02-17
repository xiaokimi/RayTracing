#include "rtpch.h"
#include "Metal.h"

Metal::Metal(const Vector3f& albedo, const float& fuzz /*= 0.0f*/)
: m_Albedo(albedo)
{
	if (fuzz < 1.0f)
	{
		m_Fuzz = fuzz;
	}
	else
	{
		m_Fuzz = 1.0f;
	}
}

Metal::~Metal()
{

}

bool Metal::scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f reflected = reflect(ray.getDirection(), record.normal);
	Vector3f fuzzDir = (reflected + m_Fuzz * getRandomInUnitSphere()).normalize();
	scattered = Ray(record.p, fuzzDir);
	attenuation = m_Albedo;
	return (dot(fuzzDir, record.normal) > 0.0f);
}
