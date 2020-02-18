#include "Sphere.h"
#include "Utils.h"
Sphere::Sphere() : Shape(Vector3(0, 0, 0), new Material(), nullptr, nullptr)
{
	m_Radius = 1;
	m_BoundingBox = CalculateBounds();
	m_Type = ShapeType::SPHERE;
}

Sphere::Sphere(Vector3 pointOfOrigin, Material *shapeMaterial, Texture* shapeTexture, Texture* objectBumpmap, float sphereRadius) : Shape(pointOfOrigin, shapeMaterial, shapeTexture, objectBumpmap)
{
	m_Radius = sphereRadius;
	m_BoundingBox = CalculateBounds();
	m_Type = ShapeType::SPHERE;
}

Sphere::~Sphere() = default;


bool Sphere::RayIntersect(const Ray& rayToCheck, float& hit_t) const
{
	Vector3 RayToSphere = rayToCheck.get_Origin() - this->GetCenter();
	float a = rayToCheck.get_Direction() * rayToCheck.get_Direction();
	float b = 2.0f * rayToCheck.get_Direction() * RayToSphere;
	float c = RayToSphere * RayToSphere - (m_Radius * m_Radius);
	float d = b * b - 4.0f * a * c;
	if (d < 0) return false;
	float t = ((-b - sqrt(d)) / (2 * a));
	if (t < 0) return false;
	hit_t = t;
	return true;

}

const Color Sphere::GetUVColor(const Vector3& hitLoc) const
{
	if (GetTexture() != nullptr)
	{
		float dx = GetNormal(hitLoc).x;
		float dy = GetNormal(hitLoc).y;
		float dz = GetNormal(hitLoc).z;

		float u = 0.5f + atan2f(dz, dx) / (2 * PI);
		float v = 0.5f - asinf(dy) / PI;

		return GetTexture()->GetData(u, v);
	}
	return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector3 Sphere::GetNormal(const Vector3& point) const
{
	Vector3 Normal(point - GetCenter());
	Normal.Normalize();
	return Normal;
}

