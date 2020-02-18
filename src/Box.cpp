#include "Box.h"

Box::Box(Vector3 LeftCorner, Vector3 TopCorner, Material* ObjectMaterial, Texture* ObjectTexture, Texture* ObjectBumpmap) : Shape(Vector3((LeftCorner + TopCorner) * 0.5f), ObjectMaterial, ObjectTexture, ObjectBumpmap)
{
	if (LeftCorner.x > TopCorner.x || LeftCorner.y > TopCorner.y || LeftCorner.z > TopCorner.z) Utilities::Swap(LeftCorner, TopCorner);
	m_VMin = LeftCorner;
	m_VMax = TopCorner;
	m_BoundingBox = CalculateBounds();
	m_Type = ShapeType::BOX;
}

bool Box::RayIntersect(const Ray& rayToCheck, float& t) const
{	
	// Based heavily on https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	Vector3 Fractal = rayToCheck.get_Direction().Inverse();

	float t1 = (m_VMin.x - rayToCheck.get_Origin().x) * Fractal.x;
	float t2 = (m_VMax.x - rayToCheck.get_Origin().x) * Fractal.x;
	float t3 = (m_VMin.y - rayToCheck.get_Origin().y) * Fractal.y;
	float t4 = (m_VMax.y - rayToCheck.get_Origin().y) * Fractal.y;
	float t5 = (m_VMin.z - rayToCheck.get_Origin().z) * Fractal.z;
	float t6 = (m_VMax.z - rayToCheck.get_Origin().z) * Fractal.z;

	float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	if (tmax < 0)
	{
		return false;
	}

	if (tmin > tmax)
	{
		return false;
	}

	t = tmin;
	return true;
}

Vector3 Box::GetNormal(const Vector3& point) const
{
	float bias = 1.0001f;
	Vector3 centerVec = point - GetCenter();
	Vector3 divisor = (m_VMin - m_VMax) * 0.5f;
	return Vector3((static_cast<int>(centerVec.x / abs(divisor.x) * bias)), (static_cast<int>(centerVec.y / abs(divisor.y) * bias)), (static_cast<int>(centerVec.z / abs(divisor.z) * bias))).Unit();
}

const Color Box::GetUVColor(const Vector3&) const
{
	return Color(1.0f, 1.0f, 1.0f, 1.0f);
}


