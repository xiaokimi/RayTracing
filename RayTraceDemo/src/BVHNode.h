#pragma once

#include "Object.h"
#include "Bounds3.h"

class BVHNode : public Object
{
public:
	BVHNode() = default;
	BVHNode(Object** objectList, const int& nCount, const float& tMin, const float& tMax);

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	Object* m_Left;
	Object* m_Right;
	Bounds3 m_Box;
};

int boxCompareByIndex(const Object* object0, const Object* object1, const int& index);

int boxCompareX(const void* a, const void* b);
int boxCompareY(const void* a, const void* b);
int boxCompareZ(const void* a, const void* b);