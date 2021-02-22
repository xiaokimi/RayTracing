#pragma once

#include "Object.h"

class FlipNormals : public Object
{
public:
	FlipNormals() = default;
	FlipNormals(Object* object);
	virtual ~FlipNormals();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	Object* m_HitObject;
};