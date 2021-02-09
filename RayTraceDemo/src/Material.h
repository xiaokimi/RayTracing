#pragma once

#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const = 0;
};