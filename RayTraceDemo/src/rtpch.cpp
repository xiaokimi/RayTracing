#include "rtpch.h"

Vector3f randomInUnitSphere()
{
	Vector3f p;
	do
	{
		p = 2.0f * Vector3f(dis(gen), dis(gen), dis(gen)) - Vector3f(1.0f, 1.0f, 1.0f);
	} while (p.lengthSquared() >= 1.0f);

	return p;
}

Vector3f randomInUnitDisk()
{
	Vector3f p;
	do
	{
		p = 2.0f * Vector3f(dis(gen), dis(gen), 0.0f) - Vector3f(1.0f, 1.0f, 0.0f);
	} while (p.lengthSquared() >= 1.0f);

	return p;
}

float schlick(const float& cosine, const float& refractiveIndex)
{
	float r0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
	r0 *= r0;
	return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5);
}

void updateProgress(const float& progress)
{
	int barWidth = 70;

	std::cout << "[";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; i++)
	{
		if (i < pos)
		{
			std::cout << "=";
		}
		else if (i == pos)
		{
			std::cout << ">";
		}
		else
		{
			std::cout << " ";
		}
	}
	std::cout << "]" << int(progress * 100.0f) << " %\r";
	std::cout.flush();
}
