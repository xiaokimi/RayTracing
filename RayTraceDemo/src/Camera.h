#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(const Point3& lookfrom, const Point3& lookat, const Vector3f& vup, const float& vfov, const float& aspect, const float& aperture, const float& focusDist);

	Ray getRay(const float& s, const float& t) const;

private:
	Point3 m_Origin;
	Point3 m_LowerLeftCorner;
	Vector3f m_Horizontal;
	Vector3f m_Vertical;

	Vector3f u, v, w;

	float m_LensRadius;
};