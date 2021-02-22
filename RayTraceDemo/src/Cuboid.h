#pragma once

#include "Object.h"

class Cuboid : public Object
{
public:
	Cuboid() = default;
	Cuboid(const Point3& pMin, const Point3& pMax, Material* material);
	virtual ~Cuboid();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	Point3 m_Min;
	Point3 m_Max;
	Object *m_ObjectList[6];
};