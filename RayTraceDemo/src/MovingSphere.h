#pragma once

#include "Object.h"
#include "Material.h"

class MovingSphere : public Object
{
public:
	MovingSphere() = default;
	MovingSphere(const Point3& center0, const Point3& center1, const float& t0, const float& t1, const float& radius, Material* material);
	~MovingSphere();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;

	Point3 getCenter(const float& time) const;

private:
	Point3 m_Center0;
	Point3 m_Center1;
	float m_Time0;
	float m_Time1;
	float m_Radius;

	Material* m_Material;
};