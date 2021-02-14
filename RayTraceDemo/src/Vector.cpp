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

Vector3f Vector3f::reflect(const Vector3f& n) const
{
	return *this - 2.0f * n.dot(*this) * n;
}

bool Vector3f::refract(const Vector3f& n, const float& niOvernt, Vector3f& refracted) const
{
	Vector3f uv = (*this).normalize();
	float dt = uv.dot(n);
	float discriminant = 1.0f - niOvernt * niOvernt * (1 - dt * dt);
	if (discriminant > 0.0f)
	{
		refracted = niOvernt * (uv - n * dt) - n * std::sqrt(discriminant);
		return true;
	}

	return false;
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
