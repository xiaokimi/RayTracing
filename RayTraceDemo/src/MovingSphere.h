#pragma once

#include "Object.h"
#include "Material.h"

class MovingSphere : public Object
{
public:
	MovingSphere() = default;
	MovingSphere(const Point3& center0, const Point3& center1, const float& tMin, const float& tMax, const float& radius, Material* material);
	~MovingSphere();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

	Point3 getCenter(const float& time) const;

private:
	Point3 m_Center0;
	Point3 m_Center1;
	float m_TimeMin;
	float m_TimeMax;
	float m_Radius;

	Material* m_Material;
};