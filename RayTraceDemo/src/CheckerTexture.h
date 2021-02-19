#pragma once

#include "Texture.h"

class CheckerTexture : public Texture
{
public:
	CheckerTexture() = default;
	CheckerTexture(Texture* odd, Texture* even);
	virtual ~CheckerTexture();

	virtual Color getColor(const float& u, const float& v, const Point3& point) const override;

private:
	Texture* m_OddTexture;
	Texture* m_EvenTexture;
};