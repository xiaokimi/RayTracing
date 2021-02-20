#include "rtpch.h"
#include "Scene.h"

Scene::Scene(int width, int height)
: m_Width(width)
, m_Height(height)
, m_BackgroundColor(0.2f, 0.6f, 0.8f)
, m_HitType(0)
, m_Root(nullptr)
, m_ObjectList(nullptr)
, m_ObjectCount(0)
{

}

Scene::~Scene()
{

}

void Scene::setBVHNode(BVHNode* root)
{
	m_Root = root;
}


void Scene::setObjectList(Object** objectList, const int& nCount)
{
	m_ObjectList = objectList;
	m_ObjectCount = nCount;
}

void Scene::setHitType(int hitType)
{
	m_HitType = hitType;
}

int Scene::getWidth() const
{
	return m_Width;
}

int Scene::getHeight() const
{
	return m_Height;
}

Color Scene::getBackgroundColor() const
{
	return m_BackgroundColor;
}

bool Scene::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	if (m_HitType == 0)
	{
		if (!m_Root)
		{
			return false;
		}

		return (m_Root->hit(ray, tMin, tMax, record));
	}
	
	//
	if (m_ObjectCount == 0)
	{
		return false;
	}

	bool hitAnything = false;
	float t = tMax;
	HitRecord temp;

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

