#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vector3f& albedo);

	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Vector3f m_Albedo;
};