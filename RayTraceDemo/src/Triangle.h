#pragma once

#include "Object.h"
#include "Material.h"

class Triangle : public Object
{
public:
	Triangle() = default;
	Triangle(Point3* vertex, Vector3f* normal, Point2* texCoord, Material* material);
	virtual ~Triangle();

	virtual bool hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const override;
	virtual bool getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const override;

private:
	void getNormal(const float& alpha, const float& beta, const float& gamma, Vector3f& normal) const;
	void getUVCoord(const float& alpha, const float& beta, const float& gamma, float& u, float& v) const;

private:
	Point3 m_Vertex[3];
	Vector3f m_Normal[3];
	Point2 m_TexCoord[3];

	Material* m_Material;
};