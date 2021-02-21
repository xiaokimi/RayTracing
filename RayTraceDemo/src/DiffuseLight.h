#pragma once

#include "Material.h"
#include "Texture.h"

class DiffuseLight : public Material
{
public:
	DiffuseLight() = default;
	DiffuseLight(Texture* texture);
	~DiffuseLight();

	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;
	virtual Color emitted(const float& u, const float& v, const Point3& point) const;
private:
	Texture* m_EmitTexture;
};