#pragma once

#include "Ray.h"

class Material;

struct HitRecord
{
	float t;
	Point3 p;
	Vector3f normal;
	Material* material;
};

class Object
{
public:
	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const = 0;
};