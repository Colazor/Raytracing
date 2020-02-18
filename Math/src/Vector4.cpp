#include "Vector4.h"


	/// Default 0 contructor
	Vector4::Vector4() : x(0), y(0), z(0), w(0) { }

	/// Constructor from components
	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	/// Constructor from components
	Vector4::Vector4(float v) : x(v), y(v), z(v), w(v) {}

	/// Returns the value of the given vector added to this.
	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	/// Returns the value of the given vector subtracted from this.
	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.z);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector4 Vector4::operator*(float value) const
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector4 Vector4::operator/(const float value) const
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}

	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Vector4::operator *(const Vector4& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	/// Adds the given vector to this.
	void Vector4::operator+=(const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	/// Subtracts the given vector from this
	void Vector4::operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	/// Multiplies this vector by the given scalar
	void Vector4::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
	}

	/// Checks if the two vectors have identical components
	bool Vector4::operator==(const Vector4& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	/// Checks if the two vectors have non-identical components
	bool Vector4::operator!=(const Vector4& other) const
	{
		return !(*this == other);
	}

	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Vector4::Dot(const Vector4& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	/// Gets the magnitude of this vector
	float Vector4::Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	/// Gets the squared magnitude of this vector
	float Vector4::SquareMagnitude() const
	{
		return x * x + y * y + z * z + w * w;
	}

	/// Limits the size of the vector to the given maximum
	void Vector4::Trim(float size)
	{
		if (SquareMagnitude() > size* size)
		{
			Normalize();
			x *= size;
			y *= size;
			z *= size;
			w *= size;
		}
	}

	Vector3 Vector4::toVec3() const
	{
		return Vector3(x, y, z);
	}
	/// Turns a non-zero vector into a vector of unit length
	void Vector4::Normalize()
	{
		float l = Magnitude();
		if (l > 0)
		{
			(*this) *= ((float)1) / l;
		}
	}

	/// Returns the normalised version of a vector
	Vector4 Vector4::Unit() const
	{
		Vector4 result = *this;	// Copy ctor
		result.Normalize();
		return result;
	}

	/// Zero all the components of the vector
	void Vector4::Clear()
	{
		x = y = z = w = 0;
	}


	/// Squared distance to another vector
	float Vector4::SquareDistance(const Vector4& other) const
	{
		return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z) + (w - other.w) * (w - other.w);
	}

/// Multiplication with Rhs Vector
inline Vector4 operator*(float val, const Vector4& rhs)
{
	return Vector4(rhs.x * val, rhs.y * val, rhs.z * val, rhs.w * val);
}
