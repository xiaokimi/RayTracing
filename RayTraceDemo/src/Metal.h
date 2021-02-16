#pragma once

#include "Material.h"

class Metal : public Matetial
{
public:
	Metal(const Vector3f& albedo, const float& fuzz = 0.0f);
	~Metal();

	virtual bool scatter(const Ray& I, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Vector3f m_Albedo;
	float m_Fuzz;
};