#pragma once

class Vector3f
{
public:
	Vector3f();
	Vector3f(const float& t);
	Vector3f(const float& xx, const float& yy, const float& zz);
	Vector3f(const Vector3f& v);

	~Vector3f();

	float x() const;
	float y() const;
	float z() const;
	float& operator[](const int& index);

	Vector3f operator-() const;

	Vector3f operator+(const float& t) const;
	Vector3f operator+(const Vector3f& v) const;
	Vector3f operator-(const float& t) const;
	Vector3f operator-(const Vector3f& v) const;
	Vector3f operator*(const float& t) const;
	Vector3f operator*(const Vector3f& v) const;
	Vector3f operator/(const float& t) const;

	Vector3f& operator+=(const float& t);
	Vector3f& operator+=(const Vector3f& v);
	Vector3f& operator-=(const float& t);
	Vector3f& operator-=(const Vector3f& v);
	Vector3f& operator*=(const float& t);
	Vector3f& operator/=(const float& t);

	float length() const;
	float lengthSquared() const;
	Vector3f normalize() const;

	friend Vector3f operator*(const float& t, const Vector3f& v);

	friend float dot(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f cross(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f reflect(const Vector3f& I, const Vector3f& N);
	friend bool refract(const Vector3f& I, const Vector3f& N, const float& ior, Vector3f& refracted);

private:
	float X;
	float Y;
	float Z;
};

using Point3 = Vector3f;
using Color = Vector3f;