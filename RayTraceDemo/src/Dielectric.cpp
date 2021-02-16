#include "rtpch.h"
#include "Dielectric.h"

Dielectric::Dielectric(const float& ior)
: m_Ior(ior)
{

}

Dielectric::~Dielectric()
{

}

bool Dielectric::scatter(const Ray& I, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	attenuation = Vector3f(1.0f, 1.0f, 1.0f);

	Vector3f refracted;
	float Kr = fresnel(I.getDirection(), record.normal, m_Ior);
	if (dis(gen) > Kr && refract(I.getDirection(), record.normal, m_Ior, refracted))
	{
		scattered = Ray(record.p, refracted);
	}
	else
	{
		Vector3f reflected = reflect(I.getDirection(), record.normal);
		scattered = Ray(record.p, reflected);
	}

	return true;
}
