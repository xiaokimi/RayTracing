#include "rtpch.h"
#include "Metal.h"

Metal::Metal(const Vector3f& albedo)
: m_Albedo(albedo)
{

}

bool Metal::scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f reflected = rayIn.getDirection().normalize().reflect(record.normal);
	scattered = Ray(record.p, reflected);
	attenuation = m_Albedo;

	return (scattered.getDirection().dot(record.normal) > 0.0f);
}
