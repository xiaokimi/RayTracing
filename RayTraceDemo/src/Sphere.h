#pragma once

#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere();
	Sphere(const Point3& center, const float& radius);
	~Sphere();

	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

private:
	Point3 m_Center;
	float m_Radius;
};