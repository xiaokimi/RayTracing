#pragma once

#include <vector>
#include <memory>

#include "Vector.h"
#include "Object.h"

class Scene
{
public:
	Scene(int width, int height);
	~Scene();

	void addObject(std::unique_ptr<Object> object);

	int getWidth() const;
	int getHeight() const;
	Color getBackgroundColor() const;

	[[nodiscard]] const std::vector<std::unique_ptr<Object>>& getAllObjects() const;

	bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const;

private:
	int m_Width;
	int m_Height;

	Color m_BackgroundColor;

	std::vector<std::unique_ptr<Object>> m_Objects;
};