#pragma once
#include "..\..\Math\src\Vector3.h"

class Ray
{
public:
	Ray();
	Ray(Vector3 rayOriginPoint, Vector3 rayOriginDirection);
	~Ray();

	const Vector3 get_Origin() const { return m_Origin; }
	const Vector3 get_Direction() const { return m_Direction; }

	void set_Origin(const Vector3 newOrigin) { m_Origin = newOrigin; }
	void set_Direction(const Vector3 newDirection) { m_Direction = newDirection; }

	Vector3 ValueAt(float t) const { return m_Origin + t * m_Direction; }

private:
	Vector3 m_Origin, m_Direction;
};