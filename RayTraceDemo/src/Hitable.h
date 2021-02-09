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

class Hitable
{
public:
	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
};