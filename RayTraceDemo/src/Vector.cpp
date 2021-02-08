#include "Vector.h"

#include <cmath>

Vector3f::Vector3f()
: X(0.0f)
, Y(0.0f)
, Z(0.0f)
{

}

Vector3f::Vector3f(float xx, float yy, float zz)
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

const Vector3f& Vector3f::operator=(const Vector3f& v)
{
	X = v.X;
	Y = v.Y;
	Z = v.Z;

	return *this;
}

Vector3f Vector3f::operator+(const Vector3f& v) const
{
	return Vector3f(X + v.X, Y + v.Y, Z + v.Z);
}

Vector3f Vector3f::operator+(const float& t) const
{
	return Vector3f(X + t, Y + t, Z + t);
}

Vector3f Vector3f::operator-(const Vector3f& v) const
{
	return Vector3f(X - v.X, Y - v.Y, Z - v.Z);
}

Vector3f Vector3f::operator-(const float& t) const
{
	return Vector3f(X - t, Y - t, Z - t);
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-X, -Y, -Z);
}

Vector3f Vector3f::operator*(const Vector3f& v) const
{
	return Vector3f(X * v.X, Y * v.Y, Z * v.Z);
}

Vector3f Vector3f::operator*(const float& t) const
{
	return Vector3f(X * t, Y * t, Z * t);
}

Vector3f Vector3f::operator/(const float& t) const
{
	return Vector3f(X / t, Y / t, Z / t);
}



Vector3f& Vector3f::operator+=(const Vector3f& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;

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

float& Vector3f::x()
{
	return X;
}

float& Vector3f::y()
{
	return Y;
}

float& Vector3f::z()
{
	return Z;
}

float Vector3f::dot(const Vector3f& v) const
{
	return X * v.X + Y * v.Y + Z * v.Z;
}

Vector3f Vector3f::cross(const Vector3f& v) const
{
	return Vector3f(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X);
}

Vector3f Vector3f::normalize() const
{
	return *this / length();
}

float Vector3f::length() const
{
	return std::sqrt(lengthSquared());
}

float Vector3f::lengthSquared() const
{
	return X * X + Y * Y + Z * Z;
}

Vector3f operator*(const float& t, const Vector3f& v)
{
	return Vector3f(v.X * t, v.Y * t, v.Z * t);
}
