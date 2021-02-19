#pragma once

#include "Vector.h"
#include "BVHNode.h"

class Scene
{
public:
	Scene(int width, int height);
	~Scene();

	void setBVHNode(BVHNode* root);

	int getWidth() const;
	int getHeight() const;
	Color getBackgroundColor() const;

	bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const;

private:
	int m_Width;
	int m_Height;

	Color m_BackgroundColor;
	
	BVHNode* m_Root;
};