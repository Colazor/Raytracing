#pragma once
#include "Ray.h"
#include "Material.h"
#include "Texture.h"
#include "AABB.h"

class Shape
{

public:

	enum class ShapeType
	{
		UNASSIGNED = 0,
		SPHERE = 1,
		BOX = 2,
		PLANE = 3
	};

	Shape();
	Shape(Vector3 pointOfOrigin, Material* objectMaterial, Texture* objectTexture, Texture* objectBumpmap);
	virtual ~Shape();

	virtual bool RayIntersect(const Ray&, float&) const { return false; }

	const Vector3 GetCenter() const { return m_Center; }
	virtual Vector3 GetNormal(const Vector3&) const { return Vector3(0.0f, 0.0f, 0.0f); };
	const Material* GetMaterial() const { return m_Material; }

	const Texture* GetTexture() const { return m_Texture; }

	const Texture* GetBumpmap() const { return m_Bumpmap; }

	virtual const Color GetUVColor(const Vector3&) const = 0;

	const AABB& GetBounds() const { return m_BoundingBox; }

	virtual const AABB CalculateBounds() const = 0;

	const ShapeType GetType() const { return m_Type; }
	

private:
	// Shape attributes and member variables
	Material *m_Material;
	Texture *m_Texture;
	Texture *m_Bumpmap;
	Vector3 m_Center;

protected:
	AABB m_BoundingBox;
	ShapeType m_Type = ShapeType::UNASSIGNED;

};