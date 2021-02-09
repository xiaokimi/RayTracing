#include "rtpch.h"
#include "Lambertian.h"

Lambertian::Lambertian(const Vector3f& albedo)
: m_Albedo(albedo)
{

}

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f target = record.p + record.normal + randomInUnitSphere();
	scattered = Ray(record.p, target - record.p);
	attenuation = m_Albedo;

	return true;
}
