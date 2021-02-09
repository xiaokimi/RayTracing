#pragma once

class Vector3f
{
public:
	Vector3f();
	Vector3f(float xx, float yy, float zz);
	Vector3f(const Vector3f& v);
	~Vector3f();

	const Vector3f& operator=(const Vector3f& v);

	Vector3f operator+(const Vector3f& v) const;
	Vector3f operator+(const float& t) const;
	Vector3f operator-(const Vector3f& v) const;
	Vector3f operator-(const float& t) const;
	Vector3f operator-() const;
	Vector3f operator*(const Vector3f& v) const;
	Vector3f operator*(const float& t) const;
	Vector3f operator/(const float& t) const;

	Vector3f& operator+=(const Vector3f& v);
	Vector3f& operator*=(const float& t);
	Vector3f& operator/=(const float& t);

	float x() const;
	float y() const;
	float z() const;

	float& x();
	float& y();
	float& z();

	float dot(const Vector3f& v) const;
	Vector3f cross(const Vector3f& v) const;
	Vector3f normalize() const;
	Vector3f reflect(const Vector3f& n) const;

	float length() const;
	float lengthSquared() const;

	friend Vector3f operator*(const float& t, const Vector3f& v);

private:
	float X;
	float Y;
	float Z;
};

using Point3 = Vector3f;
using Color = Vector3f;