#include "rtpch.h"
#include "Mat.h"

Mat3::Mat3(const float& t)
{
	m_Value[0] = Vector3f(t, 0.0f, 0.0f);
	m_Value[1] = Vector3f(0.0f, t, 0.0f);
	m_Value[2] = Vector3f(0.0f, 0.0f, t);
}

Mat3::Mat3(
	const float& x0, const float& y0, const float& z0, 
	const float& x1, const float& y1, const float& z1, 
	const float& x2, const float& y2, const float& z2)
{
	m_Value[0] = Vector3f(x0, y0, z0);
	m_Value[1] = Vector3f(x1, y1, z1);
	m_Value[2] = Vector3f(x2, y2, z2);
}

Mat3::Mat3(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2)
{
	m_Value[0] = v0;
	m_Value[1] = v1;
	m_Value[2] = v2;
}

Mat3::Mat3(const Mat3& m)
{
	for (int i = 0; i < 3; i++)
	{
		m_Value[i] = m.m_Value[i];
	}
}

Mat3::~Mat3()
{

}

Vector3f& Mat3::operator[](const int& index)
{
	return m_Value[index];
}

const Vector3f& Mat3::operator[](const int& index) const
{
	return m_Value[index];
}

Mat3 rotate(const Mat3& m, const Vector3f& axis, const float& angle)
{
	Vector3f normal = axis.normalize();
	float radius = angle * M_PI / 180.0f;
	float c = std::cosf(radius);
	float s = std::sinf(radius);

	Vector3f temp = normal * (1.0f - c);

	Mat3 rotated;
	rotated[0][0] = normal[0] * temp[0] + c;
	rotated[0][1] = normal[1] * temp[0] + normal[2] * s;
	rotated[0][2] = normal[2] * temp[0] - normal[1] * s;

	rotated[1][0] = normal[0] * temp[1] - normal[2] * s;
	rotated[1][1] = normal[1] * temp[1] + c;
	rotated[1][2] = normal[2] * temp[1] + normal[0] * s;

	rotated[2][0] = normal[0] * temp[2] + normal[1] * s;
	rotated[2][1] = normal[1] * temp[2] - normal[0] * s;
	rotated[2][2] = normal[2] * temp[2] + c;

	Mat3 result;
	result[0] = m[0] * rotated[0][0] + m[1] * rotated[0][1] + m[2] * rotated[0][2];
	result[1] = m[0] * rotated[1][0] + m[1] * rotated[1][1] + m[2] * rotated[1][2];
	result[2] = m[0] * rotated[2][0] + m[1] * rotated[2][1] + m[2] * rotated[2][2];

	return result;
}

Point3 operator*(const Mat3& m, const Point3& point)
{
	return Point3(
		dot(Vector3f(m[0][0], m[1][0], m[2][0]), point),
		dot(Vector3f(m[0][1], m[1][1], m[2][1]), point),
		dot(Vector3f(m[0][2], m[1][2], m[2][2]), point)
	);
}