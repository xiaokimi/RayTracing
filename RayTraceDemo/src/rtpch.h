#pragma once

#include <iostream>
#include <random>
#include <cmath>

#include "Vector.h"

constexpr float M_PI = 3.14159265358979323846;
constexpr float kInfinity = std::numeric_limits<float>::max();

static std::random_device dev;
static std::mt19937 gen(dev());
static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

Vector3f getRandomInUnitSphere();

float fresnel(const Vector3f& I, const Vector3f& N, const float& ior);