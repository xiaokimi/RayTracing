#include "rtpch.h"
#include "Camera.h"

Camera::Camera(const Point3& lookfrom, const Point3& lookat, const Vector3f& vup, const float& vfov, const float& aspect, const float& aperture, const float& focusDistance, const float& t0, const float& t1)
{
	//
	w = (lookfrom - lookat).normalize();
	u = cross(vup, w).normalize();
	v = cross(w, u);

	float theta = vfov * M_PI / 180.0f;
	float halfHeight = std::tan(theta / 2);
	float halfWidth = halfHeight * aspect;

	m_LensRadius = aperture / 2;
	time0 = t0;
	time1 = t1;

	m_Origin = lookfrom;
	m_LowerLeftCorner = m_Origin - (halfWidth * u + halfHeight * v + w) * focusDistance;
	m_Horizontal = 2 * halfWidth * u * focusDistance;
	m_Vertical = 2 * halfHeight * v * focusDistance;
}

Camera::~Camera()
{

}

Ray Camera::getRay(const float& s, const float& t) const
{
	Vector3f rd = m_LensRadius * getRandomInUnitDisk();
	Vector3f offset = u * rd.x() + v * rd.y();
	float time = time0 + dis(gen) * (time1 - time0);
	return Ray(m_Origin + offset, (m_LowerLeftCorner - m_Origin - offset + s * m_Horizontal + t * m_Vertical).normalize(), time);
}
