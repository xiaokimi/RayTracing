#include "rtpch.h"
#include "Renderer.h"
#include "Material.h"

Renderer::Renderer(int width, int height)
: m_Width(width)
, m_Height(height)
, m_MaxDepth(5)
{
	m_FrameBuffer.resize(width * height);

	int nCount = 5;
	for (int v = nCount - 1; v > 0; v--)
	{
		for (int u = 1; u < nCount; u++)
		{
			m_SampleArray.push_back({u * 1.0f / nCount, v * 1.0f / nCount});
		}
	}
}

Renderer::~Renderer()
{

}

void Renderer::render(const Scene& scene, const Camera& camera)
{
	for (int v = m_Height - 1; v >= 0; v--)
	{
		for (int u = 0; u < m_Width; u++)
		{
			Color color;
			for (const auto[offsetX, offsetY] : m_SampleArray)
			{
				Ray ray = camera.getRay((u * 1.0f + offsetX) / m_Width, (v * 1.0f + offsetY) / m_Height);
				color += castRay(scene, ray, 0);
			}
			
			m_FrameBuffer[(m_Height - 1 - v) * m_Width + u] = color / m_SampleArray.size();
		}
	}
}


int Renderer::getWidth() const
{
	return m_Width;
}


int Renderer::getHeight() const
{
	return m_Height;
}

const std::vector<Color>& Renderer::getFrameBuffer() const
{
	return m_FrameBuffer;
}

Color Renderer::castRay(const Scene& scene, const Ray& ray, const int& depth) const
{
	HitRecord record;
	if (scene.hit(ray, 0.001f, kInfinity, record))
	{
		Ray scattered;
		Vector3f attenuation;
		Color emitted = record.material->emitted(record.u, record.v, record.p);
		if (depth < m_MaxDepth && record.material->scatter(ray, record, attenuation, scattered))
		{
			return emitted + attenuation * castRay(scene, scattered, depth + 1);
		}
		else
		{
			return emitted;
		}
	}

	return Color(0.0f);
}

