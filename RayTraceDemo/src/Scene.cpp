#include "rtpch.h"
#include "Scene.h"

Scene::Scene(int width, int height)
: m_Width(width)
, m_Height(height)
, m_BackgroundColor(0.2f, 0.6f, 0.8f)
{

}

Scene::~Scene()
{

}

void Scene::addObject(std::unique_ptr<Object> object)
{
	m_Objects.push_back(std::move(object));
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

const std::vector<std::unique_ptr<Object>>& Scene::getAllObjects() const
{
	return m_Objects;
}

bool Scene::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	bool hitAnything = false;
	float t = tMax;

	HitRecord temp;
	for (auto& object : m_Objects)
	{
		if (object->hit(ray, tMin, t, temp))
		{
			hitAnything = true;

			t = temp.t;
			record = temp;
		}
	}

	return hitAnything;
}

