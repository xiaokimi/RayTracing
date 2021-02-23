#include "rtpch.h"
#include "Triangle.h"

Triangle::Triangle(Point3* vertex, Vector3f* normal, Point2* texCoord, Material* material)
: m_Material(material)
{
	for (int i = 0; i < 3; i++)
	{
		m_Vertex[i] = vertex[i];
		m_Normal[i] = normal[i];
		m_TexCoord[i] = texCoord[i];
	}
}

Triangle::~Triangle()
{

}

bool Triangle::hit(const Ray& ray, const float& tMin, const float& tMax, HitRecord& record) const
{
	Vector3f E1 = m_Vertex[1] - m_Vertex[0];
	Vector3f E2 = m_Vertex[2] - m_Vertex[0];
	Vector3f S = ray.getOrigin() - m_Vertex[0];
	Vector3f S1 = cross(ray.getDirection(), E2);
	Vector3f S2 = cross(S, E1);
	float coeff = 1.0f / dot(S1, E1);

	float t = coeff * dot(S2, E2);
	float beta = coeff * dot(S1, S);
	float gamma = coeff * dot(S2, ray.getDirection());
	float alpha = 1.0f - beta - gamma;

	if (t > 0.0f && alpha > 0.0f && alpha < 1.0f && beta > 0.0f && beta < 1.0f && gamma > 0.0f && gamma < 1.0f)
	{
		record.t = t;
		record.p = ray.getPosition(t);
		record.material = m_Material;

		getNormal(alpha, beta, gamma, record.normal);
		getUVCoord(alpha, beta, gamma, record.u, record.v);

		return true;
	}

	return false;
}

bool Triangle::getBoundingBox(const float& tMin, const float& tMax, Bounds3& box) const
{
	float xMin = std::fminf(m_Vertex[0].x(), std::fminf(m_Vertex[1].x(), m_Vertex[2].x()));
	float yMin = std::fminf(m_Vertex[0].y(), std::fminf(m_Vertex[1].y(), m_Vertex[2].y()));
	float zMin = std::fminf(m_Vertex[0].z(), std::fminf(m_Vertex[1].z(), m_Vertex[2].z()));

	float xMax = std::fmaxf(m_Vertex[0].x(), std::fmaxf(m_Vertex[1].x(), m_Vertex[2].x()));
	float yMax = std::fmaxf(m_Vertex[0].y(), std::fmaxf(m_Vertex[1].y(), m_Vertex[2].y()));
	float zMax = std::fmaxf(m_Vertex[0].z(), std::fmaxf(m_Vertex[1].z(), m_Vertex[2].z()));

	Point3 offset = Vector3f(1.0f).normalize() * 0.001f;

	box = Bounds3(Point3(xMin, yMin, zMin) - offset, Point3(xMax, yMax, zMax) + offset);
	return true;
}

void Triangle::getNormal(const float& alpha, const float& beta, const float& gamma, Vector3f& normal) const
{
	normal = alpha * m_Normal[0] + beta * m_Normal[1] + gamma * m_Normal[2];
}

void Triangle::getUVCoord(const float& alpha, const float& beta, const float& gamma, float& u, float& v) const
{
	Vector2f texCoord = alpha * m_TexCoord[0] + beta * m_TexCoord[1] + gamma * m_TexCoord[2];
	u = texCoord.x();
	v = texCoord.y();
}
