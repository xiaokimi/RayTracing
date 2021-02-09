#pragma once

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList();
	HitableList(Hitable** list, const int& size);

	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

private:
	Hitable **m_List;
	int m_Size;
};