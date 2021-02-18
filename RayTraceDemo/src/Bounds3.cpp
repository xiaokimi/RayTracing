#include "rtpch.h"
#include "Bounds3.h"

Bounds3::Bounds3(const Point3& pMin, const Point3& pMax)
: m_Min(pMin)
, m_Max(pMax)
{

}

Bounds3::~Bounds3()
{

}

Point3 Bounds3::getPointMin() const
{
	return m_Min;
}

Point3 Bounds3::getPointMax() const
{
	return m_Max;
}

bool Bounds3::hit(const Ray& ray, float tMin, float tMax) const
{
	Point3 origin = ray.getOrigin();
	Vector3f direction = ray.getDirection();

	Point3 pMin = getPointMin();
	Point3 pMax = getPointMax();

	for (int index = 0; index < 3; index++)
	{
		float invD = 1.0f / direction[index];
		float t0 = (pMin[index] - origin[index]) * invD;
		float t1 = (pMax[index] - origin[index]) * invD;
		if (invD < 0.0f)
		{
			std::swap(t0, t1);
		}

		tMin = std::fmaxf(t0, tMin);
		tMax = std::fminf(t1, tMax);

		if (tMax <= tMin)
		{
			return false;
		}
	}

	return true;
}

Bounds3 getSurroundingBox(const Bounds3& box0, const Bounds3& box1)
{
	Point3 pMin0 = box0.getPointMin();
	Point3 pMin1 = box1.getPointMin();
	float xMin = std::fminf(pMin0.x(), pMin1.x());
	float yMin = std::fminf(pMin0.y(), pMin1.y());
	float zMin = std::fminf(pMin0.z(), pMin1.z());

	Point3 pMax0 = box0.getPointMax();
	Point3 pMax1 = box1.getPointMax();
	float xMax = std::fmaxf(pMax0.x(), pMax1.x());
	float yMax = std::fmaxf(pMax0.y(), pMax1.y());
	float zMax = std::fmaxf(pMax0.z(), pMax1.z());

	return Bounds3(Point3(xMin, yMin, zMin), Point3(xMax, yMax, zMax));
}
