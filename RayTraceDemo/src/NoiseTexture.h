#pragma once

#include "Texture.h"

class NoiseTexture : public Texture
{
public:
	NoiseTexture();
	~NoiseTexture();

	virtual Color getColor(const float& u, const float& v, const Point3& point) const override;
};