#include "rtpch.h"
#include "AxisAlignedRect.h"

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

bool XYRect::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	Point3 deltaP = Point3(0.0f, 0.0f, 0.0001f);
	box = Bounds3(m_Min - deltaP, m_Max + deltaP);
	return true;
}

XZRect::XZRect(const Point3& pMin, const Point3& pMax, Material* material)
: m_Min(pMin)
, m_Max(pMax)
, m_Material(material)
{

}

XZRect::~XZRect()
{

}

bool XZRect::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	float t = (m_Min.y() - ray.getOrigin().y()) / ray.getDirection().y();
	if (t < tMin || t > tMax)
	{
		return false;
	}

	Point3 p = ray.getPosition(t);
	float x = p.x();
	float z = p.z();
	if (x < m_Min.x() || x > m_Max.x() || z < m_Min.z() || z > m_Max.z())
	{
		return false;
	}

	record.t = t;
	record.u = (x - m_Min.x()) / (m_Max.x() - m_Min.x());
	record.v = (z - m_Min.z()) / (m_Max.z() - m_Min.z());
	record.p = p;
	record.normal = Vector3f(0.0f, 1.0f, 0.0f);
	record.material = m_Material;

	return true;
}

bool XZRect::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	Point3 deltaP = Point3(0.0f, 0.0001f, 0.0f);
	box = Bounds3(m_Min - deltaP, m_Max + deltaP);
	return true;
}

YZRect::YZRect(const Point3& pMin, const Point3& pMax, Material* material)
: m_Min(pMin)
, m_Max(pMax)
, m_Material(material)
{

}

YZRect::~YZRect()
{

}

bool YZRect::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	float t = (m_Min.x() - ray.getOrigin().x()) / ray.getDirection().x();
	if (t < tMin || t > tMax)
	{
		return false;
	}

	Point3 p = ray.getPosition(t);
	float y = p.y();
	float z = p.z();
	if (y < m_Min.y() || y > m_Max.y() || z < m_Min.z() || z > m_Max.z())
	{
		return false;
	}

	record.t = t;
	record.u = (y - m_Min.y()) / (m_Max.y() - m_Min.y());
	record.v = (z - m_Min.z()) / (m_Max.z() - m_Min.z());
	record.p = p;
	record.normal = Vector3f(1.0f, 0.0f, 0.0f);
	record.material = m_Material;

	return true;
}

bool YZRect::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	Point3 deltaP = Point3(0.0001f, 0.0f, 0.0f);
	box = Bounds3(m_Min - deltaP, m_Max + deltaP);
	return true;
}