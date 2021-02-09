#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(const float& refractiveIndex);
	~Dielectric();

	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	float m_RefractiveIndex;
};