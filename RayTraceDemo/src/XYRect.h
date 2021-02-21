#pragma once

#include "Object.h"
#include "Material.h"

class XYRect : public Object
{
public:
	XYRect() = default;
	XYRect(const Point3& pMin, const Point3& pMax, Material* material);
	virtual ~XYRect();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& t0, const float& t1, Bounds3& box) const override;

private:
	Point3 m_Min;
	Point3 m_Max;

	Material* m_Material;
};