#include "rtpch.h"
#include "Camera.h"

Camera::Camera(const Point3& lookfrom, const Point3& lookat, const Vector3f& vup, const float& vfov, const float& aspect, const float& aperture, const float& focusDist)
{
	m_LensRadius = aperture / 2;

	w = (lookfrom - lookat).normalize();
	u = vup.cross(w).normalize();
	v = w.cross(u);

	float theta = vfov * M_PI / 180.0f;
	float halfHeight = std::tan(theta / 2);
	float halfWidth = halfHeight * aspect;

	m_Origin = lookfrom;
	m_LowerLeftCorner = m_Origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
	m_Horizontal = 2 * halfWidth * focusDist * u;
	m_Vertical = 2 * halfHeight * focusDist * v;
}

Ray Camera::getRay(const float& s, const float& t) const
{
	Vector3f rd = m_LensRadius * randomInUnitDisk();
	Vector3f offset = u * rd.x() + v * rd.y();

	return Ray(m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset);
}
