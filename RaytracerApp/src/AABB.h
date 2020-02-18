#pragma once
#include "..\..\Math\src\Vector3.h"
#include "Ray.h"

class AABB
{
public:
	AABB(const Vector3 minPos, const Vector3 maxPos) : m_VMin(minPos), m_VMax(maxPos) { ; };
	AABB(const AABB& c) 
	{
		m_VMin = c.m_VMin;
		m_VMax = c.m_VMax;
	}
	AABB()
	{
		AABB(Vector3::Zero(), Vector3::Zero());
	}

	const float GetRadius(unsigned int Axis) const
	{ 
		switch (Axis)
		{
			case 1:
				return (m_VMax.x - m_VMin.x) * 0.5f;
				break;
			case 2:
				return (m_VMax.y - m_VMin.y) * 0.5f;
				break;
			case 3:
				return (m_VMax.z - m_VMin.z) * 0.5f;
				break;
		}
	}
	const Vector3& GetMin() const { return m_VMin; };
	const Vector3& GetMax() const { return m_VMax; };

	void SetMin(const Vector3& n_min) { m_VMin = n_min; }
	void SetMax(const Vector3& n_max) { m_VMax = n_max; }

	static const AABB NULL_BOUNDARY() { return AABB(); }
	static const AABB INFINITE_BOUNDARY() { return AABB(Vector3(-INFINITY, -INFINITY, -INFINITY), Vector3(INFINITY, INFINITY, INFINITY)); }
	
	const bool RayIntersect(const Ray& rayToCheck) const
	{
		if (*this == INFINITE_BOUNDARY()) return false;
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

		 if (tmin < 0) return false;
		return true;
	}

	const bool operator== (const AABB& rhs) const
	{
		return ((rhs.m_VMax == m_VMax) && (rhs.m_VMin == m_VMin));
	}

	const bool operator!= (const AABB& rhs) const
	{
		return !(operator==(rhs));
	}


private:
	Vector3 m_VMin, m_VMax;
};


