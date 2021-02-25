#include "rtpch.h"
#include "Cuboid.h"
#include "AxisAlignedRect.h"
#include "FlipNormals.h"

Cuboid::Cuboid(Object** objectList, const int& nCount)
: m_ObjectList(objectList)
, m_ObjectCount(nCount)
{
	
}

Cuboid::~Cuboid()
{

}

bool Cuboid::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	bool hitAnything = false;

	HitRecord temp;
	float t = tMax;

	for (int i = 0; i < m_ObjectCount; i++)
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
	Bounds3 tempBox;
	if (!m_ObjectList[0]->getBoundingBox(tMin, tMax, tempBox))
	{
		return false;
	}

	box = tempBox;
	for (int i = 1; i < m_ObjectCount; i++)
	{
		if (m_ObjectList[i]->getBoundingBox(tMin, tMax, tempBox))
		{
			box = getSurroundingBox(box, tempBox);
		}
		else
		{
			return false;
		}
	}

	return true;
}
