#pragma once

#include "Object.h"
#include "Material.h"

class Sphere : public Object
{
public:
	Sphere(const Point3& center, const float& radius, Matetial* matetial);
	~Sphere();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;

private:
	Point3 m_Center;
	float m_Radius;

	Matetial* m_Matetial;
};