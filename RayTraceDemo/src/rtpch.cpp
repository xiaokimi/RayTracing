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