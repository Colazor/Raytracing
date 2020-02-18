#include "Shape.h"

Shape::Shape() : m_Center(), m_Material(), m_Texture(nullptr), m_Bumpmap(nullptr) {}
Shape::~Shape() {}
Shape::Shape(Vector3 centerPoint, Material* objectMaterial, Texture* objectTexture, Texture* objectBumpmap)
{
	m_Center = centerPoint;
	m_Material = objectMaterial;
	m_Texture = objectTexture;
	m_Bumpmap = objectBumpmap;

}


