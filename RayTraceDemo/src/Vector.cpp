#include "rtpch.h"
#include "Vector.h"

Vector3f::Vector3f()
: X(0.0f)
, Y(0.0f)
, Z(0.0f)
{

}

Vector3f::Vector3f(const float& t)
: X(t)
, Y(t)
, Z(t)
{

}

Vector3f::Vector3f(const float& xx, const float& yy, const float& zz)
: X(xx)
, Y(yy)
, Z(zz)
{

}

Vector3f::Vector3f(const Vector3f& v)
: X(v.X)
, Y(v.Y)
, Z(v.Z)
{

}

Vector3f::~Vector3f()
{

}

float Vector3f::x() const
{
	return X;
}

float Vector3f::y() const
{
	return Y;
}

float Vector3f::z() const
{
	return Z;
}

float& Vector3f::operator[](const int& index)
{
	switch (index)
	{
	case 0:
	{
		return X;
		break;
	}
	case 1:
	{
		return Y;
		break;
	}
	case 2:
	{
		return Z;
		break;
	}
	}
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-X, -Y, -Z);
}

Vector3f Vector3f::operator+(const float& t) const
{
	return Vector3f(X + t, Y + t, Z + t);
}

Vector3f Vector3f::operator+(const Vector3f& v) const
{
	return Vector3f(X + v.X, Y + v.Y, Z + v.Z);
}

Vector3f Vector3f::operator-(const float& t) const
{
	return Vector3f(X - t, Y - t, Z - t);
}

Vector3f Vector3f::operator-(const Vector3f& v) const
{
	return Vector3f(X - v.X, Y - v.Y, Z - v.Z);
}

Vector3f Vector3f::operator*(const float& t) const
{
	return Vector3f(X * t, Y * t, Z * t);
}

Vector3f Vector3f::operator*(const Vector3f& v) const
{
	return Vector3f(X * v.X, Y * v.Y, Z * v.Z);
}

Vector3f Vector3f::operator/(const float& t) const
{
	return Vector3f(X / t, Y / t, Z / t);
}

Vector3f& Vector3f::operator+=(const float& t)
{
	X += t;
	Y += t;
	Z += t;

	return *this;
}

Vector3f& Vector3f::operator+=(const Vector3f& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;

	return *this;
}

Vector3f& Vector3f::operator-=(const float& t)
{
	X -= t;
	Y -= t;
	Z -= t;

	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;

	return *this;
}

Vector3f& Vector3f::operator*=(const float& t)
{
	X *= t;
	Y *= t;
	Z *= t;

	return *this;
}

Vector3f& Vector3f::operator/=(const float& t)
{
	X /= t;
	Y /= t;
	Z /= t;

	return *this;
}

float Vector3f::length() const
{
	return std::sqrtf(X * X + Y * Y + Z * Z);
}

float Vector3f::lengthSquared() const
{
	return X * X + Y * Y + Z * Z;
}

Vector3f Vector3f::normalize() const
{
	float divNum = length();
	return Vector3f(X / divNum, Y / divNum, Z / divNum);
}

Vector3f operator*(const float& t, const Vector3f& v)
{
	return Vector3f(v.X * t, v.Y * t, v.Z * t);
}

float dot(const Vector3f& v1, const Vector3f& v2)
{
	return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
}

Vector3f cross(const Vector3f& v1, const Vector3f& v2)
{
	return Vector3f(v1.Y * v2.Z - v1.Z * v2.Y, v1.Z * v2.X - v1.X * v2.Z, v1.X * v2.Y - v1.Y * v2.X);
}

Vector3f reflect(const Vector3f& I, const Vector3f& N)
{
	return I - 2 * dot(I, N) * N;
}

bool refract(const Vector3f& I, const Vector3f& N, const float& ior, Vector3f& refracted)
{
	float etai = 1.0f;
	float etat = ior;
	Vector3f normal = N;

	float cosi = dot(I, N);
	if (cosi > 0)
	{
		cosi = -cosi;
		normal = -N;
		std::swap(etai, etat);
	}

	float eta = etai / etat;
	float discriminant = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (discriminant > 0.0f)
	{
		refracted = eta * I - (eta * cosi + std::sqrtf(discriminant)) * normal;
		return true;
	}

	return false;
}
