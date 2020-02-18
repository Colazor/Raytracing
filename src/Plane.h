#pragma once
#include "Shape.h"

class Plane : public Shape
{
public:
	Plane();
	~Plane();
	Plane(Vector3 pointOnPlane, Vector3 Normal, Material *shapeMaterial, Texture* shapeTexture, Texture* shapeBumpmap);
	
	bool RayIntersect(const Ray& rayToCheck, float& hit_t) const;

	Vector3 get_Point() const { return Shape::GetCenter(); }

	Vector3 GetNormal(const Vector3&) const
	{
		return m_Normal;
	}

	virtual const Color GetUVColor(const Vector3& hit) const;

	virtual const AABB CalculateBounds() const
	{
		return AABB::INFINITE_BOUNDARY();
	}


private:
	Vector3 m_Normal;
};