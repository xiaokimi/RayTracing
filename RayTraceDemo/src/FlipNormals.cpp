#include "rtpch.h"
#include "FlipNormals.h"

FlipNormals::FlipNormals(Object* object)
: m_HitObject(object)
{

}

FlipNormals::~FlipNormals()
{

}

bool FlipNormals::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	if (m_HitObject->hit(ray, tMin, tMax, record))
	{
		record.normal = -record.normal;
		return true;
	}

	return false;
}

bool FlipNormals::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	return m_HitObject->getBoundingBox(tMin, tMax, box);
}
