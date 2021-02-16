#include "rtpch.h"
#include "Camera.h"

Camera::Camera()
{
	m_Origin = Point3(0.0f, 0.0f, 0.0f);
	m_LowerLeftCorner = Point3(-2.0f, -1.0f, -1.0f);
	m_Horizontal = Vector3f(4.0f, 0.0f, 0.0f);
	m_Vertical = Vector3f(0.0f, 2.0f, 0.0f);
}

Camera::~Camera()
{

}

Ray Camera::getRay(const float& s, const float& t) const
{
	return Ray(m_Origin, (m_LowerLeftCorner - m_Origin + s * m_Horizontal + t * m_Vertical).normalize());
}
