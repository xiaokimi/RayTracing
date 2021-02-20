#include "rtpch.h"
#include "PerlinNoise.h"

PerlinNoise& PerlinNoise::getInstance()
{
	static PerlinNoise m_Noise;
	return m_Noise;
}

float PerlinNoise::getNoise(const Point3& point) const
{
	//float u = point.x() - std::floorf(point.x());
	//float v = point.y() - std::floorf(point.y());
	//float w = point.z() - std::floorf(point.z());

	int i = int(4 * point.x()) & 255;
	int j = int(4 * point.y()) & 255;
	int k = int(4 * point.z()) & 255;

	return m_RandomFloat[m_PermX[i] ^ m_PermY[j] ^ m_PermZ[k]];
}

PerlinNoise::PerlinNoise()
{
	std::cout << "Perlin Noise create...\n";

	perlinGenerate();
	perlinGeneratePerm(m_PermX);
	perlinGeneratePerm(m_PermY);
	perlinGeneratePerm(m_PermZ);
}

PerlinNoise::~PerlinNoise()
{

}

void PerlinNoise::perlinGenerate()
{
	for (int i = 0; i < PerlinSize; i++)
	{
		m_RandomFloat[i] = dis(gen);
	}
}

void PerlinNoise::permute(int* p)
{
	for (int i = PerlinSize - 1; i > 0; i--)
	{
		int target = dis(gen) * (i + 1);
		std::swap(p[i], p[target]);
	}
}

void PerlinNoise::perlinGeneratePerm(int* p)
{
	for (int i = 0; i < PerlinSize; i++)
	{
		p[i] = i;
	}

	permute(p);
}
