#pragma once

#include "Vector.h"

class Mat3
{
public:
	Mat3() = default;
	Mat3(const float& t);
	Mat3(
		const float& x0, const float& y0, const float& z0,
		const float& x1, const float& y1, const float& z1,
		const float& x2, const float& y2, const float& z2
	);
	Mat3(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
	Mat3(const Mat3& m);
	~Mat3();

	Vector3f& operator[](const int& index);
	const Vector3f& operator[](const int& index) const;

	/**
	 * axis = (ax, ay, az)  c = cos(theta)  s = sin(theta)
	 *
	 * | ax*ax*(1-c) + c,    ax*ay*(1-c) - az*s, ax*az*(1-c) + ay*s |
	 * | ax*ay*(1-c) + az*s, ay*ay*(1-c) + c,    ay*az*(1-c) - ax*s |
	 * | ax*az*(10c) - ay*s, ay*az*(1-c) + ax*s, az*az*(1-c) + c    |
	 *
	**/
	friend Mat3 rotate(const Mat3& m, const Vector3f& axis, const float& angle);

	friend Point3 operator*(const Mat3& m, const Point3& point);

private:
	Vector3f m_Value[3];
};