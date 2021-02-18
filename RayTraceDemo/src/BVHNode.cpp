#include "rtpch.h"
#include "BVHNode.h"

BVHNode::BVHNode(Object** l, const int& nCount, const float& t0, const float& t1)
{

}

bool BVHNode::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	if (m_Box.hit(ray, tMin, tMax))
	{
		HitRecord leftRecord, rightRecord;
		bool hitLeft = m_Left->hit(ray, tMin, tMax, leftRecord);
		bool hitRight = m_Right->hit(ray, tMin, tMax, rightRecord);
		if (hitLeft && hitRight)
		{
			record = leftRecord.t < rightRecord.t ? leftRecord : rightRecord;
			return true;
		}
		else if (hitLeft)
		{
			record = leftRecord;
			return true;
		}
		else if (hitRight)
		{
			record = rightRecord;
			return true;
		}
	}

	return false;
}

bool BVHNode::getBoundingBox(const float& t0, const float& t1, Bounds3& box) const
{
	box = m_Box;
	return true;
}
