#pragma once
#include <cmath>
#include "Vector3.h"

class Vector4
{
public:

	float x, y, z, w;

public:
	Vector4();

	Vector4(float x, float y, float z, float w);

	explicit Vector4(float v);

	Vector4 operator+(const Vector4& v) const;

	Vector4 operator-(const Vector4& v) const;

	Vector4 operator*(float value) const;

	Vector4 operator/(const float value) const;

	float operator *(const Vector4& vector) const;

	void operator+=(const Vector4& v);

	void operator-=(const Vector4& v);

	/// Multiplies this vector by the given scalar
	void operator*=(const float value);

	/// Checks if the two vectors have identical components
	bool operator==(const Vector4& other) const;
	/// Checks if the two vectors have non-identical components
	bool operator!=(const Vector4& other) const;

	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Dot(const Vector4& vector) const;

	/// Gets the magnitude of this vector
	float Magnitude() const;

	/// Gets the squared magnitude of this vector
	float SquareMagnitude() const;

	/// Limits the size of the vector to the given maximum
	void Trim(float size);

	Vector3 toVec3() const;
	/// Turns a non-zero vector into a vector of unit length
	void Normalize();

	/// Returns the normalised version of a vector
	Vector4 Unit() const;

	/// Zero all the components of the vector
	void Clear();


	/// Squared distance to another vector
	float SquareDistance(const Vector4& other) const;

	static Vector4 Zero;	

};