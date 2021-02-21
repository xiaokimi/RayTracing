#pragma once

#include "Object.h"
#include "Material.h"

class Sphere : public Object
{
public:
	Sphere(const Point3& center, const float& radius, Material* matetial);
	~Sphere();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& t0, const float& t1, Bounds3& box) const override;

	void getUVCoord(const Point3& point, float& u, float& v) const;

private:
	Point3 m_Center;
	float m_Radius;

	Material* m_Material;
};