#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Vector3f& albedo);
	
	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Vector3f m_Albedo;
};