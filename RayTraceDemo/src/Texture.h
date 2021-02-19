#pragma once

#include "Vector.h"

class Texture
{
public:
	virtual Color getColor(const float& u, const float& v, const Point3& point) const = 0;
};