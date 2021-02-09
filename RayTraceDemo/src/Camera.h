#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera();

	Ray getRay(const float& u, const float& v) const;

private:
	Point3 m_Origin;
	Point3 m_LowerLeftCorner;
	Vector3f m_Horizontal;
	Vector3f m_Vertical;
};