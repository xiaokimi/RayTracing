#include "rtpch.h"
#include "PerlinNoise.h"

PerlinNoise& PerlinNoise::getInstance()
{
	static PerlinNoise m_Noise;
	return m_Noise;
}

float PerlinNoise::getNoise(const Point3& point) const
{
	float u = point.x() - std::floorf(point.x());
	float v = point.y() - std::floorf(point.y());
	float w = point.z() - std::floorf(point.z());

	int i = std::floorf(point.x());
	int j = std::floorf(point.y());
	int k = std::floorf(point.z());

	Vector3f c[2][2][2];
	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				c[di][dj][dk] = m_RandomVector[m_PermX[(i + di) & 255] ^ m_PermY[(j + dj) & 255] ^ m_PermZ[(k + dk) & 255]];
			}
		}
	}

	return trilinearInterp(c, u, v, w);
}

float PerlinNoise::getTurb(const Point3& point, const int& depth /*= 7*/) const
{
	float accum = 0.0f;
	float weight = 1.0f;
	Vector3f temp = point;
	for (int i = 0; i < depth; i++)
	{
		accum += weight * getNoise(temp);
		weight *= 0.5f;
		temp *= 2;
	}
	return std::fabsf(accum);
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
		m_RandomVector[i] = Vector3f(-1.0f + 2 * dis(gen), -1.0f + 2 * dis(gen), -1.0f + 2 * dis(gen)).normalize();
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

float PerlinNoise::trilinearInterp(Vector3f c[2][2][2], float u, float v, float w) const
{
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);

	float accum = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Vector3f weightV(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) *
					(j * vv + (1 - j) * (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weightV);
			}
		}
	}

	return accum;
}
