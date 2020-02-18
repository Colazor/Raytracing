#include "Plane.h"

// By default will return a normal of UnitZ and initial point of 0
Plane::Plane() : Shape(Vector3(), new Material(), nullptr, nullptr)
{
	m_Normal = Vector3(0, 0, 0);
	m_BoundingBox = CalculateBounds();
	m_Type = ShapeType::PLANE;
}

Plane::~Plane()
{

}

Plane::Plane(Vector3 pointOnPlane, Vector3 normalOfPlane, Material *shapeMaterial, Texture *shapeTexture, Texture* shapeBumpmap) : Shape(pointOnPlane, shapeMaterial, shapeTexture,  shapeBumpmap)
{
	m_Normal = normalOfPlane;
	m_Normal = m_Normal.Unit();
	m_BoundingBox = CalculateBounds();
	m_Type = ShapeType::PLANE;


}

bool Plane::RayIntersect(const Ray& rayToCheck, float& hit_t) const
{
	const float epsilon = 0.00001f;

	float disc = rayToCheck.get_Direction() * m_Normal;
	if (disc > epsilon || disc < -epsilon)
	{
		Vector3 PtoO = get_Point() - rayToCheck.get_Origin();
		float t = (PtoO * m_Normal) / disc;
		if (t < epsilon) return false;
		hit_t = t;
		return true;
	}
	else 
	{
		return false;
	}
}

const Color Plane::GetUVColor(const Vector3& hit) const
{
	int hitx = static_cast<int>(floor(hit.x));
	int hity = static_cast<int>(floor(hit.y));
	int hitz = static_cast<int>(floor(hit.z));

	Vector3 N = GetNormal(hit);
	int Ny = static_cast<int>(abs(N.y));
	int Nz = static_cast<int>(abs(N.z));

	if (Ny == 1)
	{
		int square = hitx + hitz;
		if (square % 2 == 0) return Color(0.0f, 0.0f, 0.0f, 1.0f);
		return Color(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (Nz == 1)
	{
		int square = hitx + hity;
		if (square % 2 == 0) return Color(0.0f, 0.0f, 0.0f, 1.0f);
		return Color(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		int square = hity + hitz;
		if (square % 2 == 0) return Color(0.0f, 0.0f, 0.0f, 1.0f);
		return Color(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
}
