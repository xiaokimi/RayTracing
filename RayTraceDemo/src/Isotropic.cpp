#include "rtpch.h"
#include "Isotropic.h"

Isotropic::Isotropic(Texture* albedo)
: m_Albedo(albedo)
{

}

Isotropic::~Isotropic()
{

}

bool Isotropic::scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	scattered = Ray(record.p, getRandomInUnitSphere());
	attenuation = m_Albedo->getColor(record.u, record.v, record.p);
	return true;
}
