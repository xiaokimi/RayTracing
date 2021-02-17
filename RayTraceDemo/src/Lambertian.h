#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vector3f& albedo);
	~Lambertian();

	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Vector3f m_Albedo;
};