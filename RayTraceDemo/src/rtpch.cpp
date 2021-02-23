#include "rtpch.h"

float* convertToSRGB(const int& width, const int& height, const unsigned char* pixels)
{
	int dataSize = width * height * 3;
	float *srgb = new float[dataSize];

	for (int i = 0; i < dataSize; i++)
	{
		srgb[i] = std::powf(pixels[i] / 255.0f, M_GAMMA);
	}

	return srgb;
}

Vector3f getRandomInUnitSphere()
{
	Vector3f p;
	do 
	{
		p = 2.0f * Vector3f(dis(gen), dis(gen), dis(gen)) - Vector3f(1.0f, 1.0f, 1.0f);
	} while (p.lengthSquared() >= 1.0f);

	return p;
}

Vector3f getRandomInUnitDisk()
{
	Vector3f p;
	do
	{
		p = 2.0f * Vector3f(dis(gen), dis(gen), 0) - Vector3f(1.0f, 1.0f, 0.0f);
	} while (p.lengthSquared() >= 1.0f);

	return p;
}

float fresnel(const Vector3f& I, const Vector3f& N, const float& ior)
{
	float cosi = dot(I, N);
	float etai = 1.0f, etat = ior;
	if (cosi > 0.0f)
	{
		std::swap(etai, etat);
	}

	float sint = etai / etat * std::sqrtf(1.0f - cosi * cosi);
	if (sint >= 1.0f)
	{
		return 1.0f;
	}

	float cost = std::sqrtf(1.0f - sint * sint);
	cosi = std::fabs(cosi);

	float Rs = (etat * cosi - etai * cost) / (etat * cosi + etai * cost);
	float Rp = (etai * cosi - etat * cost) / (etai * cosi + etat * cost);

	return (Rs * Rs + Rp * Rp) / 2;
}
