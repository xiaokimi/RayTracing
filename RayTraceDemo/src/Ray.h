#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& orig, const Vector3f& dir, const float& time = 0.0f);
	~Ray();

	Point3 getOrigin() const;
	Vector3f getDirection() const;
	float getTime() const;
	Point3 getPosition(const float& t) const;

private:
	Point3 m_Origin;
	Vector3f m_Direction;
	float m_Time;
};