#pragma once

#include "Texture.h"

class ConstantTexture : public Texture
{
public:
	ConstantTexture() = default;
	ConstantTexture(const Color& color);
	virtual ~ConstantTexture();

	virtual Color getColor(const float& u, const float& v, const Point3& point) const override;

private:
	Color m_Color;
};