#include "rtpch.h"
#include "Lambertian.h"

Lambertian::Lambertian(Texture* albedo)
: m_Albedo(albedo)
{

}

Lambertian::~Lambertian()
{

}

bool Lambertian::scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f target = record.p + record.normal + getRandomInUnitSphere();
	scattered = Ray(record.p, (target - record.p).normalize(), ray.getTime());
	attenuation = m_Albedo->getColor(0.0f, 0.0f, record.p);

	return true;
}
