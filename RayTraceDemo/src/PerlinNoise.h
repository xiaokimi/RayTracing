#pragma once

#include "Vector.h"

constexpr int PerlinSize = 256;

class PerlinNoise
{
public:
	static PerlinNoise& getInstance();

	float getNoise(const Point3& point) const;
private:
	PerlinNoise();
	~PerlinNoise();

	void perlinGenerate();
	void permute(int* p);
	void perlinGeneratePerm(int* p);

private:
	float m_RandomFloat[PerlinSize];
	int m_PermX[PerlinSize];
	int m_PermY[PerlinSize];
	int m_PermZ[PerlinSize];
};