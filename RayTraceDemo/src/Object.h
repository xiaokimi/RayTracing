#pragma once

#include "Ray.h"
#include "Bounds3.h"

class Material;

struct HitRecord
{
	float t;
	float u;
	float v;
	Point3 p;
	Vector3f normal;
	Material* material;
};

class Object
{
public:
	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const = 0;
	virtual bool getBoundingBox(const float& t0, const float& t1, Bounds3& box) const = 0;
};