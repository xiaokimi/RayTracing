#pragma once

#include "Ray.h"
#include "Object.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const = 0;
	virtual Color emitted(const float& u, const float& v, const Point3& point) const
	{
		return Color(0.0f);
	}
};