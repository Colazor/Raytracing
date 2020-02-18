#pragma once
#include "Vector3.h"

	/// Default 0 contructor
	Vector3::Vector3() : x(0), y(0), z(0) {}

	/// Constructor from components
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3::Vector3(int x, int y, int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

	/// Constructor from components
	Vector3::Vector3(float v) : x(v), y(v), z(v) {}

	/// Returns the value of the given vector added to this.
	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	/// Returns a vector with all values of the float added to each separate axis

	Vector3 Vector3::operator+(const float f) const
	{
		return Vector3(x + f, y + f, z + f);
	}
	/// Returns a vector with all values of the float deduced from each separate axis

	Vector3 Vector3::operator-(const float f) const
	{
		return Vector3(x - f, y - f, z - f);
	}
	/// Returns the value of the given vector subtracted from this.
	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector3 Vector3::operator*(float value) const
	{
		return Vector3(x * value, y * value, z * value);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector3 Vector3::operator/(const float value) const
	{
		return Vector3(x / value, y / value, z / value);
	}


	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Vector3::operator *(const Vector3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	/// Adds the given vector to this.
	void Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(x - abs(x) * 2, y - abs(y) * 2, z - abs(z) * 2);
	}
	/// Subtracts the given vector from this
	void Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	/// Multiplies this vector by the given scalar
	void Vector3::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	void Vector3::operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;
	}

	/// Checks if the two vectors have identical components
	bool Vector3::operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	/// Checks if the two vectors have non-identical components
	bool Vector3::operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Vector3::Dot(const Vector3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	/// Cross product in 3D
	Vector3 Vector3::Cross(const Vector3& rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	/// Gets the magnitude of this vector
	float Vector3::Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	/// Gets the squared magnitude of this vector
	float Vector3::SquareMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	/// Limits the size of the vector to the given maximum
	void Vector3::Trim(float size)
	{
		if (SquareMagnitude() > size* size)
		{
			Normalize();
			x *= size;
			y *= size;
			z *= size;
		}
	}

	/// Turns a non-zero vector into a vector of unit length
	void Vector3::Normalize()
	{
		float l = Magnitude();
		if (l > 0)
		{
			(*this) *= ((float)1) / l;
		}
	}

	/// Returns the normalised version of a vector
	Vector3 Vector3::Unit() const
	{
		Vector3 result = *this;	// Copy ctor
		result.Normalize();
		return result;
	}

	Vector3 Vector3::Inverse() const
	{
		return Vector3(1 / x, 1 / y, 1 / z);
	}

	/// Returns the perpendicular of the vector
	Vector3 Vector3::Perpendicular() const
	{
		Vector3 result(z, y, -x);
		return result;
	}

	bool Vector3::CheckNormalized() const
	{
		float check = Magnitude();
		bool truthvalue = ((check > 0.999f) && (check < 1.001f));
		return truthvalue;
	}

	/// Zero all the components of the vector
	void Vector3::Clear()
	{
		x = y = z = 0;
	}


	/// Squared distance to another vector
	float Vector3::SquareDistance(const Vector3& other) const
	{
		return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
	}

	const Vector3 Vector3::UnitZ()
	{
		return Vector3(0, 0, 1);
	}

	const Vector3 Vector3::Zero()
	{
		return Vector3();
	}
	// // Incident Direction - 2 * SurfaceNormal * DotProduct(Incident Direction, SurfaceNormal)

	 Vector3 Vector3::Reflect(const Vector3& rayDir, const Vector3& surfaceNormal)
	{
		return (rayDir - surfaceNormal * 2 * rayDir.Dot(surfaceNormal));
	}

	Vector3 Vector3::Refract(const Vector3& RayDirection, const Vector3& SurfaceNormal, const float MaterialRefractionIndex, float& Fresnel, const float MediumRefractionIndex)
	{
		float CosI = Utilities::ClampValue(1, -1, SurfaceNormal * RayDirection);
		float TempMatIndex = MaterialRefractionIndex;
		float TempMedIndex = MediumRefractionIndex;
		Vector3 TempNormal(SurfaceNormal);
		if (CosI < 0) CosI = -CosI;
		else
		{
			Utilities::Swap(TempMatIndex, TempMedIndex);
			TempNormal = -TempNormal;
		}
		// Fresnel calculation part
		float SinT = TempMedIndex / TempMatIndex * sqrtf(fmaxf(0.0f, 1 - CosI * CosI));
		if (SinT >= 1) Fresnel = 1.0f;
		else
		{
			float CosT = sqrtf(fmaxf(0.0f, 1 - SinT * SinT));
			float Rs = ((TempMatIndex * CosI) - (TempMedIndex * CosT)) / ((TempMatIndex * CosI) + (TempMedIndex * CosT));
			float Rp = ((TempMedIndex * CosI) - (TempMatIndex * CosT)) / ((TempMedIndex * CosI) + (TempMatIndex * CosT));
			Fresnel = (Rs * Rs + Rp * Rp) / 2;

		}
		// End of Fresnel calculation
		float IndexOfRefraction = TempMatIndex / TempMedIndex;
		float KVal = 1 - IndexOfRefraction * IndexOfRefraction * (1 - CosI * CosI);
		return KVal < 0 ? Zero() : (RayDirection * IndexOfRefraction + TempNormal * (IndexOfRefraction * CosI - sqrtf(KVal)));
	}

