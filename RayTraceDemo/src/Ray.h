#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray();
	Ray(const Point3& orig, const Vector3f& dir);

	~Ray();

	Point3 getOrigin() const;
	Vector3f getDirection() const;

	Point3 at(const float& t) const;

private:
	Point3 m_Orig;
	Vector3f m_Dir;
};