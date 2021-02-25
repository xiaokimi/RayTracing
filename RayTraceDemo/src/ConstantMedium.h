#pragma once

#include "Object.h"
#include "Material.h"

class ConstantMedium : public Object
{
public:
	ConstantMedium() = default;
	ConstantMedium(Object* object, const float& density, Material* material);
	virtual ~ConstantMedium();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	Object* m_Object;
	float m_Density;
	Material* m_Material;
};