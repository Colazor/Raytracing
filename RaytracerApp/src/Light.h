#pragma once
#include "..\..\Math\src\Vector3.h"
#include "Color.h"

class Light
{
public:
	enum class LightType
	{
		DIRECTIONAL = 0,
		POINT = 1,
		FLASHLIGHT = 2
	};
	Light() : m_Color(), m_Type(LightType::DIRECTIONAL), m_Position() {}
	Light(Vector3 locationOfLight, Color &colorOfLight, LightType typeOfLight) : m_Color(colorOfLight), m_Type(typeOfLight), m_Position(locationOfLight) {}
	
	Vector3 GetPosition() const { return m_Position; }
	Color GetColor() const { return m_Color; }

	float DistanceToLight(const Vector3& Point) const
	{
		if (m_Type == LightType::DIRECTIONAL)
		{
			return INFINITY;
		}
		else
		{
			return (m_Position - Point).Magnitude();
		}
	}
	virtual Vector3 GetLightDirection(const Vector3&) const = 0;
	virtual float GetLightAmount(const Vector3&) const = 0;
	virtual float GetLightPower() const = 0;

	
protected:
	Vector3 m_Position;
	LightType m_Type;
	Color m_Color;
};