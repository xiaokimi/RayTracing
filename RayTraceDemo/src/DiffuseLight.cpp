#include "rtpch.h"
#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(Texture* texture)
: m_EmitTexture(texture)
{

}

DiffuseLight::~DiffuseLight()
{

}

bool DiffuseLight::scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	return false;
}

Color DiffuseLight::emitted(const float& u, const float& v, const Point3& point) const
{
	return m_EmitTexture->getColor(u, v, point);
}
