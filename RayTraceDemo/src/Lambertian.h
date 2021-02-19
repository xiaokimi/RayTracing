#pragma once

#include "Material.h"
#include "Texture.h"

class Lambertian : public Material
{
public:
	Lambertian(Texture* albedo);
	~Lambertian();

	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Texture* m_Albedo;
};