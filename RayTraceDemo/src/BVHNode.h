#pragma once

#include "Object.h"
#include "Bounds3.h"

class BVHNode : public Object
{
public:
	BVHNode() = default;
	BVHNode(Object** l, const int& nCount, const float& t0, const float& t1);

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& t0, const float& t1, Bounds3& box) const override;

private:
	Object* m_Left;
	Object* m_Right;
	Bounds3 m_Box;
};