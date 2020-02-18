#pragma once
#include <cmath>
#include "Utils.h"

class Vector3
{
public:
	float x, y, z;

public:

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(int x, int y, int z);
	explicit Vector3(float v);
	Vector3 operator+(const Vector3& v) const;

	Vector3 operator+(const float f) const;

	Vector3 operator-(const float f) const;
	Vector3 operator-(const Vector3& v) const;

	Vector3 operator*(float value) const;

	Vector3 operator/(const float value) const;

	float operator *(const Vector3& vector) const;

	void operator+=(const Vector3& v);

	Vector3 operator-() const;
	void operator-=(const Vector3& v);

	void operator*=(const float value);

	void operator/=(const float value);

	bool operator==(const Vector3& other) const;

	bool operator!=(const Vector3& other) const;
	float Dot(const Vector3& vector) const;

	Vector3 Cross(const Vector3& rhs) const;
	float Magnitude() const;

	float SquareMagnitude() const;

	void Trim(float size);
	void Normalize();

	Vector3 Unit() const;

	Vector3 Inverse() const;
	Vector3 Perpendicular() const;

	bool CheckNormalized() const;
	void Clear();
	float SquareDistance(const Vector3& other) const;

	static const Vector3 UnitZ();

	static const Vector3 Zero();
	static Vector3 Reflect(const Vector3& rayDir, const Vector3& surfaceNormal);

	static Vector3 Refract(const Vector3& RayDirection, const Vector3& SurfaceNormal, const float MaterialRefractionIndex, float& Fresnel, const float MediumRefractionIndex = 1.0f);

};

inline Vector3 operator*(float val, const Vector3& rhs)
{
	return Vector3(rhs.x * val, rhs.y * val, rhs.z * val);
}
