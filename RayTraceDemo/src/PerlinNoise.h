#pragma once

#include "Vector.h"

constexpr int PerlinSize = 256;

class PerlinNoise
{
public:
	static PerlinNoise& getInstance();

	float getNoise(const Point3& point) const;
	float getTurb(const Point3& point, const int& depth = 7) const;
private:
	PerlinNoise();
	~PerlinNoise();

	void perlinGenerate();
	void permute(int* p);
	void perlinGeneratePerm(int* p);

	float trilinearInterp(Vector3f c[2][2][2], float u, float v, float w) const;
private:
	Vector3f m_RandomVector[PerlinSize];
	int m_PermX[PerlinSize];
	int m_PermY[PerlinSize];
	int m_PermZ[PerlinSize];
};