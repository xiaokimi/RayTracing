#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(const float& ior);
	~Dielectric();

	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	float m_Ior;
};