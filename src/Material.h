#pragma once
#include "Color.h"
class Material
{
public:

	Material(Color diffuseColor, Color specularColor, Color ambientColor, float shineValue, float reflection, float refraction) : m_Diffuse(diffuseColor), m_Specular(specularColor),
		m_Ambient(ambientColor), m_Shininess(shineValue), m_Reflectiveness(fmin(reflection, 1.0f)), m_RefractionIndex(refraction) {}

	Material() : m_Diffuse(Color(0, 0, 0, 0)), m_Specular(Color(0, 0, 0, 0)),
		m_Ambient(Color(0, 0, 0, 0)), m_Shininess(0), m_Reflectiveness(0), m_RefractionIndex(0) {}

	const Color GetDiffuse() const { return m_Diffuse; }
	const Color GetSpecular() const { return m_Specular; }
	const Color GetAmbient() const { return m_Ambient; }
	const float GetShininess() const { return m_Shininess; }
	const float GetReflectiveness() const { return m_Reflectiveness; }

	const float GetRefractiveIndex() const { return m_RefractionIndex; }
	
	void SetDiffuse(Color newDiffuse) { m_Diffuse = newDiffuse; }
	void SetSpecular(Color newSpecular) { m_Specular = newSpecular; }
	void SetAmbient(Color newAmbient) { m_Ambient = newAmbient; }
	void SetShininess(float newShininess) { m_Shininess = newShininess; }
	void SetReflectiveness(float newReflection) { m_Reflectiveness = fmin(newReflection, 1.0f); }

	void SetRefractiveIndex(float newRefraction) { m_RefractionIndex = newRefraction; }


	static Material EXAMPLE_BRONZE() 
	{
		return Material(Color(1.0f, 0.0f, 0.0f, 1.0f), Color(0.5f, 0.5f, 0.5f, 1.0f), Color(1.0f, 0.0f, 0.0f, 1.0f), 64.f, 0.0f, 0.0f);
	}
	static Material EXAMPLE_EMERALD()
	{
		return Material(Color(0.07568f, 0.61424f, 0.07568f, 1.0f), Color(0.633f, 0.727811f, 0.633f, 1.0f), Color(0.0215f, 0.1745f, 0.0215f, 1.0f), 77.0f, 0.0f, 0.0f);
	}

	static Material EXAMPLE_SILVER()
	{
		return Material(Color(0.50754f, 0.50754f, 0.50754f, 1.0f), Color(0.508273f, 0.508273f, 0.508273f, 1.0f), Color(0.19225f, 0.19225f, 0.19225f, 1.0f), 51.2f, 0.0f, 0.0f);
	}

	static Material EXAMPLE_REFLECTIVE_MATERIAL()
	{
		return Material(Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 64.0f, 1.0f, 0.0f);
	}

	static Material EXAMPLE_FULL_COLOR_MATERIAL()
	{
		return Material(Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 16.f, 0.0f, 0.0f);
	}

	static Material EXAMPLE_HALF_REFRACTIVE_MATERIAL()
	{
		return Material(Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 64.f, 0.9f, 0.9f);
	}

private:
	Color m_Diffuse, m_Specular, m_Ambient;
	float m_RefractionIndex;
	float m_Reflectiveness;
	float m_Shininess;
};