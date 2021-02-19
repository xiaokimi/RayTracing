#include "rtpch.h"
#include "Scene.h"

Scene::Scene(int width, int height)
: m_Width(width)
, m_Height(height)
, m_BackgroundColor(0.2f, 0.6f, 0.8f)
, m_Root(nullptr)
{

}

Scene::~Scene()
{

}

void Scene::setBVHNode(BVHNode* root)
{
	m_Root = root;
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
	if (!m_Root)
	{
		return false;
	}
		
	return (m_Root->hit(ray, tMin, tMax, record));
}

