#include "rtpch.h"
#include "Cuboid.h"
#include "AxisAlignedRect.h"
#include "FlipNormals.h"

Cuboid::Cuboid(const Point3& pMin, const Point3& pMax, Material* material)
: m_Min(pMin)
, m_Max(pMax)
{
	m_ObjectList[0] = new FlipNormals(new XYRect(pMin, Point3(pMax.x(), pMax.y(), pMin.z()), material));
	m_ObjectList[1] = new XYRect(Point3(pMin.x(), pMin.y(), pMax.z()), pMax, material);
	m_ObjectList[2] = new FlipNormals(new XZRect(pMin, Point3(pMax.x(), pMin.y(), pMax.z()), material));
	m_ObjectList[3] = new XZRect(Point3(pMin.x(), pMax.y(), pMin.z()), pMax, material);
	m_ObjectList[4] = new FlipNormals(new YZRect(pMin, Point3(pMin.x(), pMax.y(), pMax.z()), material));
	m_ObjectList[5] = new YZRect(Point3(pMax.x(), pMin.y(), pMin.z()), pMax, material);
}

Cuboid::~Cuboid()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_ObjectList[i])
		{
			delete m_ObjectList[i];
			m_ObjectList[i] = nullptr;
		}
	}
}

bool Cuboid::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	bool hitAnything = false;

	HitRecord temp;
	float t = tMax;

	for (int i = 0; i < 6; i++)
	{
		if (m_ObjectList[i]->hit(ray, tMin, t, temp))
		{
			hitAnything = true;

			t = temp.t;
			record = temp;
		}
	}

	return hitAnything;
}

bool Cuboid::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	box = Bounds3(m_Min, m_Max);
	return true;
}
