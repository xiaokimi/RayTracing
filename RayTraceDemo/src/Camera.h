#pragma once

#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	~Camera();

	Ray getRay(const float& s, const float& t) const;

private:
	Point3 m_Origin;
	Point3 m_LowerLeftCorner;
	Vector3f m_Horizontal;
	Vector3f m_Vertical;
};