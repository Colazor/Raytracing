#include "Ray.h"
// Default constructor for zero origin and zero direction
Ray::Ray() : m_Origin(), m_Direction() {}

Ray::Ray(Vector3 rayOriginPoint, Vector3 rayDirection)
{
	m_Origin = rayOriginPoint;
	m_Direction = rayDirection;
}

Ray::~Ray()
{
	
}
