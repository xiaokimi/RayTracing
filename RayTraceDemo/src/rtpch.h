#pragma once

#include <iostream>
#include <cmath>
#include <random>

#define _USE_MATH_DEFINES
#include <math.h>


#include "Vector.h"

//
constexpr float MAXFLOAT = std::numeric_limits<float>::max();

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

//
Vector3f randomInUnitSphere();
Vector3f randomInUnitDisk();

float schlick(const float& cosine, const float& refractiveIndex);

void updateProgress(const float& progress);