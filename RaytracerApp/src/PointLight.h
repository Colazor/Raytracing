#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	// Vector3 position, Color* colorOfLight, float intensity, LightType typeOfLight
	PointLight(Color &colorOfLight, Vector3 locationOfLight, float lightRange) : Light(locationOfLight, colorOfLight, LightType::POINT)
	{
		m_Power = lightRange * 0.2f;
	}

	Vector3 GetLightDirection(const Vector3& p) const
	{
		return (m_Position - p);
	}
	Vector3 a = Light::GetPosition();
	
	float GetLightAmount(const Vector3& p) const
	{
		float d = DistanceToLight(p);
		return 1 / (1 * +(m_Linear * d) + (m_Quadratic * pow(d, 2))) * m_Power;
	}

	float GetLightPower() const
	{
		return m_Power;
	}

private:
	// Default lighting value is to the range of 20
	// Linear very small, quadratic = 1 for physically accurate formula 
	float m_Linear = 0.22f, m_Quadratic = 0.20f;
	float m_Power;
};
