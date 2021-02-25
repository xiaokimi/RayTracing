#pragma once

#include "Material.h"
#include "Texture.h"

class Isotropic : public Material
{
public:
	Isotropic() = default;
	Isotropic(Texture* albedo);
	virtual ~Isotropic();

	virtual bool scatter(const Ray& ray, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;

private:
	Texture* m_Albedo;
};