#pragma once

#include "Texture.h"

class NoiseTexture : public Texture
{
public:
	NoiseTexture(const float& scale = 1.0f);
	~NoiseTexture();

	virtual Color getColor(const float& u, const float& v, const Point3& point) const override;

private:
	float m_Scale;
};