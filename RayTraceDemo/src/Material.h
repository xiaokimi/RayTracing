#pragma once

#include "Ray.h"
#include "Object.h"

class Matetial
{
public:
	virtual bool scatter(const Ray& I, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const = 0;
};