#pragma once

#include <iostream>
#include <random>
#include <cmath>

#include "Vector.h"

constexpr float M_PI = 3.14159265358979323846f;
constexpr float M_GAMMA = 2.2f;
constexpr float kInfinity = std::numeric_limits<float>::max();

static std::random_device dev;
static std::mt19937 gen(dev());
static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

template<typename T>
T lerp(const T& tMin, const T& tMax, const T& t)
{
	return std::max<T>(tMin, std::min<T>(tMax, t));
}

float* convertToSRGB(const int& width, const int& height, const unsigned char* pixels);

Vector3f getRandomInUnitSphere();
Vector3f getRandomInUnitDisk();

float fresnel(const Vector3f& I, const Vector3f& N, const float& ior);