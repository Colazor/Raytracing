#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	// Vector3 position, Color* colorOfLight, float intensity, LightType typeOfLight
	DirectionalLight(Vector3 directionOfLight, Color &colorOfLight, Vector3 locationOfLight) : Light(locationOfLight, colorOfLight, LightType::DIRECTIONAL)
	{
		m_Direction = directionOfLight;
	}

	Vector3 GetLightDirection(const Vector3&) const
	{
		return m_Direction;
	}

	float GetLightAmount(const Vector3&) const
	{
		// Directional lights have no multiplier for the fade off since they hit from infinite distance
		return 1.0f;
	}

	float GetLightPower() const
	{
		return 1.0f;
	}
private:
	Vector3 m_Direction;
};