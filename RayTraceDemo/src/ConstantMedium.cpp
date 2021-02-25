#include "rtpch.h"
#include "ConstantMedium.h"

ConstantMedium::ConstantMedium(Object* object, const float& density, Material* material)
: m_Object(object)
, m_Density(density)
, m_Material(material)
{

}

ConstantMedium::~ConstantMedium()
{

}

bool ConstantMedium::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	bool db = (dis(gen) < 0.00001f);
	db = false;

	HitRecord record1, record2;
	if (m_Object->hit(ray, -kInfinity, kInfinity, record1))
	{
		if (m_Object->hit(ray, record1.t + 0.0001f, kInfinity, record2))
		{
			if (record1.t < tMin)
			{
				record1.t = tMin;
			}

			if (record2.t > tMax)
			{
				record2.t = tMax;
			}

			if (record1.t > record2.t)
			{
				return false;
			}

			float distanceInsideObject = ray.getDirection().length() * (record2.t - record1.t);
			float hitDistance = -(1.0f / m_Density) * std::logf(dis(gen));
			if (hitDistance < distanceInsideObject)
			{
				record.t = record1.t + hitDistance / ray.getDirection().length();
				record.p = ray.getPosition(record.t);
				record.normal = Vector3f(1.0f, 0.0f, 0.0f);
				record.material = m_Material;

				return true;
			}
		}
	}

	return false;
}

bool ConstantMedium::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	return m_Object->getBoundingBox(tMin, tMax, box);
}
