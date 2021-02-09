#include "rtpch.h"
#include "Metal.h"

Metal::Metal(const Vector3f& albedo, const float& fuzz)
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

bool Metal::scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f reflected = rayIn.getDirection().normalize().reflect(record.normal);
	scattered = Ray(record.p, reflected + m_Fuzz * randomInUnitSphere());
	attenuation = m_Albedo;

	return (scattered.getDirection().dot(record.normal) > 0.0f);
}
