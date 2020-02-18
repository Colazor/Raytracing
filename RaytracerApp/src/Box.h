#pragma once
#include "Shape.h"

class Box : public Shape
{
public:
	Box(Vector3 LeftCorner, Vector3 TopCorner, Material* ObjectMaterial, Texture* ObjectTexture, Texture* ObjectBumpmap);

	Box() : Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), nullptr, nullptr, nullptr) {	m_Type = ShapeType::BOX; }
	~Box() { }
	bool RayIntersect(const Ray&, float&) const;
	Vector3 GetNormal(const Vector3& point) const;
	const Color GetUVColor(const Vector3&) const;

	virtual const AABB CalculateBounds() const
	{
		return AABB(m_VMin, m_VMax);
	}


private:
	Vector3 m_VMin, m_VMax;
};