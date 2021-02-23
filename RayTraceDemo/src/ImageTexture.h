#pragma once

#include "Texture.h"

class ImageTexture : public Texture
{
public:
	ImageTexture() = default;
	ImageTexture(const int& width, const int& height, float* srgb);
	~ImageTexture();

	Color getColor(const float& u, const float& v, const Point3& point) const;

private:
	int m_Width;
	int m_Height;
	float* m_SRGB;
};