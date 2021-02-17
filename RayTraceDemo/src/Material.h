#pragma once

#include "Ray.h"
#include "Object.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const = 0;
};