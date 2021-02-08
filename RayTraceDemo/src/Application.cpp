#include "Vector.h"

#include <iostream>

int main()
{
	Vector3f v1(1.0f, 1.0f, 1.0f);

	Vector3f v2 = v1 * 3.0f;

	std::cin.get();
}