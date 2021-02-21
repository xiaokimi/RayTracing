#pragma once

#include "Texture.h"

class ImageTexture : public Texture
{
public:
	ImageTexture() = default;
	ImageTexture(const int& width, const int& height, unsigned char* pixels);
	~ImageTexture();

	Color getColor(const float& u, const float& v, const Point3& point) const;

private:
	int m_Width;
	int m_Height;
	unsigned char* m_Data;
};