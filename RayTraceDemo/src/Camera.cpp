#include "rtpch.h"
#include "Camera.h"

Camera::Camera()
: m_Origin(0.0f, 0.0f, 0.0f)
, m_LowerLeftCorner(-2.0f, -1.0f, -1.0f)
, m_Horizontal(4.0f, 0.0f, 0.0f)
, m_Vertical(0.0f, 2.0f, 0.0f)
{

}

Ray Camera::getRay(const float& u, const float& v) const
{
	return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin);
}
