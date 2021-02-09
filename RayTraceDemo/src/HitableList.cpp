#include "rtpch.h"
#include "HitableList.h"

HitableList::HitableList()
: m_List(nullptr)
, m_Size(0)
{

}

HitableList::HitableList(Hitable** list, const int& size)
: m_List(list)
, m_Size(size)
{

}

bool HitableList::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	bool hitAnything = false;
	float t = tMax;
	HitRecord tempRecord;

	for (int i = 0; i < m_Size; i++)
	{
		if (m_List[i]->hit(ray, tMin, t, tempRecord))
		{
			hitAnything = true;
			t = tempRecord.t;
			record = tempRecord;
		}
	}

	return hitAnything;
}
