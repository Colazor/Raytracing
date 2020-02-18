#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere();
	~Sphere();
	Sphere(Vector3 pointOfOrigin, Material *objectMaterial, Texture *objectTexture, Texture *objectBumpmap, float sphereRadius);
	bool RayIntersect(const Ray& rayToCheck, float& hit_t) const;

	float get_Radius() const { return m_Radius; }
	Vector3 GetNormal(const Vector3& point) const;
	virtual const Color GetUVColor(const Vector3& hitLoc) const;

	virtual const AABB CalculateBounds() const
	{
		return AABB(GetCenter() - get_Radius(), GetCenter() + get_Radius());
	}


private:
	float m_Radius;
};