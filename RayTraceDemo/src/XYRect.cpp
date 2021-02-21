#include "rtpch.h"
#include "XYRect.h"

XYRect::XYRect(const Point3& pMin, const Point3& pMax, Material* material)
: m_Min(pMin)
, m_Max(pMax)
, m_Material(material)
{

}

XYRect::~XYRect()
{

}

bool XYRect::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	float t = (m_Min.z() - ray.getOrigin().z()) / ray.getDirection().z();
	if (t < tMin || t > tMax)
	{
		return false;
	}

	Point3 p = ray.getPosition(t);
	float x = p.x();
	float y = p.y();
	if (x < m_Min.x() || x > m_Max.x() || y < m_Min.y() || y > m_Max.y())
	{
		return false;
	}

	record.t = t;
	record.u = (x - m_Min.x()) / (m_Max.x() - m_Min.x());
	record.v = (y - m_Min.y()) / (m_Max.y() - m_Min.y());
	record.p = p;
	record.normal = Vector3f(0.0f, 0.0f, 1.0f);
	record.material = m_Material;

	return true;
}

bool XYRect::getBoundingBox(const float& t0, const float& t1, Bounds3& box) const
{
	Point3 deltaP = Point3(0.0f, 0.0f, 0.0001f);
	box = Bounds3(m_Min - deltaP, m_Max + deltaP);
	return true;
}
