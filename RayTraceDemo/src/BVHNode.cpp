#include "rtpch.h"
#include "BVHNode.h"

BVHNode::BVHNode(Object** objectList, const int& nCount, const float& t0, const float& t1)
{
	int axis = int(3 * dis(gen));
	if (axis == 0)
		qsort(objectList, nCount, sizeof(Object*), boxCompareX);
	else if (axis == 1)
		qsort(objectList, nCount, sizeof(Object*), boxCompareY);
	else
		qsort(objectList, nCount, sizeof(Object*), boxCompareZ);

	if (nCount == 1)
	{
		m_Left = m_Right = objectList[0];
	}
	else if (nCount == 2)
	{
		m_Left = objectList[0];
		m_Right = objectList[1];
	}
	else
	{
		m_Left = new BVHNode(objectList, nCount / 2, t0, t1);
		m_Right = new BVHNode(objectList + nCount / 2, nCount - nCount / 2, t0, t1);
	}
	
	Bounds3 boxLeft, boxRight;
	if (!m_Left->getBoundingBox(t0, t1, boxLeft) || !m_Right->getBoundingBox(t0, t1, boxRight))
	{
		std::cerr << "Error\n";
	}

	m_Box = getSurroundingBox(boxLeft, boxRight);
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

int boxCompareByIndex(const Object* object0, const Object* object1, const int& index)
{
	Bounds3 box0, box1;
	if (!object0->getBoundingBox(0.0f, 0.0f, box0) || !object1->getBoundingBox(0.0f, 0.0f, box1))
	{
		std::cerr << "Error\n";
	}

	if (box0.getPointMin()[index] - box1.getPointMin()[index] < 0.0f)
	{
		return -1;
	}

	return 1;
}

int boxCompareX(const void* a, const void* b)
{
	return boxCompareByIndex(*(Object**)a, *(Object**)b, 0);
}

int boxCompareY(const void* a, const void* b)
{
	return boxCompareByIndex(*(Object**)a, *(Object**)b, 1);
}

int boxCompareZ(const void* a, const void* b)
{
	return boxCompareByIndex(*(Object**)a, *(Object**)b, 2);
}
