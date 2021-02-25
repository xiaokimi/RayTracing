#pragma once

#include "Object.h"

class Cuboid : public Object
{
public:
	Cuboid() = default;
	Cuboid(Object** objectList, const int& nCount);
	virtual ~Cuboid();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	Object** m_ObjectList;
	int m_ObjectCount;
};