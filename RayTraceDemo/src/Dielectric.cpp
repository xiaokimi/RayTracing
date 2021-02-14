#include "rtpch.h"
#include "Dielectric.h"

Dielectric::Dielectric(const float& refractiveIndex)
: m_RefractiveIndex(refractiveIndex)
{

}

Dielectric::~Dielectric()
{

}

bool Dielectric::scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f outwardNormal;
	Vector3f reflected = rayIn.getDirection().reflect(record.normal);
	float niOvernt;
	attenuation = Vector3f(1.0f, 1.0f, 1.0f);
	Vector3f refracted;
	float refractProb;
	float cosine;
	if (rayIn.getDirection().dot(record.normal) > 0)
	{
		outwardNormal = -record.normal;
		niOvernt = m_RefractiveIndex;
		cosine = m_RefractiveIndex * rayIn.getDirection().dot(record.normal) / rayIn.getDirection().length();
	}
	else
	{
		outwardNormal = record.normal;
		niOvernt = 1.0f / m_RefractiveIndex;
		cosine = -rayIn.getDirection().dot(record.normal) / rayIn.getDirection().length();
	}

	if (rayIn.getDirection().refract(outwardNormal, niOvernt, refracted))
	{
		refractProb = schlick(cosine, m_RefractiveIndex);
	}
	else
	{
		scattered = Ray(record.p, reflected);
		refractProb = 1.0f;
		
	}

	if (dis(gen) < refractProb)
	{
		scattered = Ray(record.p, reflected);
	}
	else
	{
		scattered = Ray(record.p, refracted);
	}

	return true;
}
