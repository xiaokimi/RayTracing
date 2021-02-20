#pragma once

#include <vector>
#include <tuple>

#include "Vector.h"
#include "Scene.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void render(const Scene& scene, const Camera& camera);

	int getWidth() const;
	int getHeight() const;
	[[nodiscard]] const std::vector<Color>& getFrameBuffer() const;

private:
	Color castRay(const Scene& scene, const Ray& ray, const int& depth) const;

private:
	int m_Width;
	int m_Height;
	int m_MaxDepth;
	std::vector<Color> m_FrameBuffer;

	std::vector<std::tuple<float, float>> m_SampleArray;
};