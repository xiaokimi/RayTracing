#pragma once

#include "Material.h"

class Dielectric : public Matetial
{
public:
	Dielectric(const float& ior);
	~Dielectric();

	virtual bool scatter(const Ray& I, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	float m_Ior;
};