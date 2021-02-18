#pragma once

#include "Vector.h"
#include "Ray.h"

class Bounds3
{
public:
	Bounds3() = default;
	Bounds3(const Point3& pMin, const Point3& pMax);
	~Bounds3();

	Point3 getPointMin() const;
	Point3 getPointMax() const;

	bool hit(const Ray& ray, float tMin, float tMax) const;

private:
	Point3 m_Min;
	Point3 m_Max;
};

Bounds3 getSurroundingBox(const Bounds3& box0, const Bounds3& box1);