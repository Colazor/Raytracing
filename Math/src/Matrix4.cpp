#include "Matrix4.h"


	Matrix4::Matrix4()
	{
		x1 = 1;
		y1 = 0;
		z1 = 0;
		w1 = 0;

		x2 = 0;
		y2 = 1;
		z2 = 0;
		w2 = 0;

		x3 = 0;
		y3 = 0;
		z3 = 1;
		w3 = 0;

		x4 = 0;
		y4 = 0;
		z4 = 0;
		w4 = 1;
	}

	Matrix4::Matrix4(const Vector4& c1, const Vector4& c2, const Vector4& c3, const Vector4& c4)
	{
		x1 = c1.x;
		y1 = c1.y;
		z1 = c1.z;
		w1 = c1.w;

		x2 = c2.x;
		y2 = c2.y;
		z2 = c2.z;
		w2 = c2.w;

		x3 = c3.x;
		y3 = c3.y;
		z3 = c3.z;
		w3 = c3.w;

		x4 = c4.x;
		y4 = c4.y;
		z4 = c4.z;
		w4 = c4.w;
	}

	Matrix4::Matrix4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->z1 = z1;
		this->w1 = w1;

		this->x2 = x2;
		this->y2 = y2;
		this->z2 = z2;
		this->w2 = w2;

		this->x3 = x3;
		this->y3 = y3;
		this->z3 = z3;
		this->w3 = w3;

		this->x4 = x4;
		this->y4 = y4;
		this->z4 = z4;
		this->w4 = w4;
	}
	Matrix4::Matrix4(float v)
	{
		x1 = v; y1 = v; z1 = v; w1 = v;
		x2 = v; y2 = v; z2 = v; w2 = v;
		x3 = v; y3 = v; z3 = v; w3 = v;
		x4 = v; y4 = v; z4 = v; w4 = v;
	}
	Matrix4 Matrix4::Identity() const
	{
		return Matrix4();
	}

	Matrix4 Matrix4::operator+(const Matrix4& m) const
	{
		return Matrix4
		(
			x1 + m.x1, y1 + m.y1, z1 + m.z1, w1 + m.w1,
			x2 + m.x2, y2 + m.y2, z2 + m.z2, w2 + m.w2,
			x3 + m.x3, y3 + m.y3, z3 + m.z3, w3 + m.w3,
			x4 + m.x4, y4 + m.y4, z4 + m.z4, w4 + m.w4
		);
	}

	void Matrix4::operator+=(const Matrix4& m)
	{
		x1 += m.x1, y1 += m.y1, z1 += m.z1, w1 += m.w1,
			x2 += m.x2, y2 += m.y2, z2 += m.z2, w2 += m.w2,
			x3 += m.x3, y3 += m.y3, z3 += m.z3, w3 += m.w3,
			x4 += m.x4, y4 += m.y4, z4 += m.z4, w4 += m.w4;
	}

	Matrix4 Matrix4::operator-(const Matrix4& m) const
	{
		return Matrix4
		(
			x1 - m.x1, y1 - m.y1, z1 - m.z1, w1 - m.w1,
			x2 - m.x2, y2 - m.y2, z2 - m.z2, w2 - m.w2,
			x3 - m.x3, y3 - m.y3, z3 - m.z3, w3 - m.w3,
			x4 - m.x4, y4 - m.y4, z4 - m.z4, w4 - m.w4
		);
	}

	void Matrix4::operator-=(const Matrix4& m)
	{
			x1 -= m.x1, y1 -= m.y1, z1 -= m.z1, w1 -= m.w1,
			x2 -= m.x2, y2 -= m.y2, z2 -= m.z2, w2 -= m.w2,
			x3 -= m.x3, y3 -= m.y3, z3 -= m.z3, w3 -= m.w3,
			x4 -= m.x4, y4 -= m.y4, z4 -= m.z4, w4 -= m.w4;
	}
	Vector4 Matrix4::operator*(const Vector4& m) const
	{
		return Vector4
		(
			x1 * m.x + x2 * m.y + x3 * m.z + x4 * m.w,
			y1 * m.x + y2 * m.y + y3 * m.z + y4 * m.w,
			z1 * m.x + z2 * m.y + z3 * m.z + z4 * m.w,
			w1 * m.x + w2 * m.y + w3 * m.z + w4 * m.w
		);
	}

	Matrix4 Matrix4::operator*(const Matrix4& m) const
	{
		return Matrix4
		(
			x1 * m.x1 + x2 * m.y1 + x3 * m.z1 + x4 * m.w1,
			y1 * m.x1 + y2 * m.y1 + y3 * m.z1 + y4 * m.w1,
			z1 * m.x1 + z2 * m.y1 + z3 * m.z1 + z4 * m.w1,
			w1 * m.x1 + w2 * m.y1 + w3 * m.z1 + w4 * m.w1,

			x1 * m.x2 + x2 * m.y2 + x3 * m.z2 + x4 * m.w2,
			y1 * m.x2 + y2 * m.y2 + y3 * m.z2 + y4 * m.w2,
			z1 * m.x2 + z2 * m.y2 + z3 * m.z2 + z4 * m.w2,
			w1 * m.x2 + w2 * m.y2 + w3 * m.z2 + w4 * m.w2,

			x1 * m.x3 + x2 * m.y3 + x3 * m.z3 + x4 * m.w3,
			y1 * m.x3 + y2 * m.y3 + y3 * m.z3 + y4 * m.w3,
			z1 * m.x3 + z2 * m.y3 + z3 * m.z3 + z4 * m.w3,
			w1 * m.x3 + w2 * m.y3 + w3 * m.z3 + w4 * m.w3,

			x1 * m.x4 + x2 * m.y4 + x3 * m.z4 + x4 * m.w4,
			y1 * m.x4 + y2 * m.y4 + y3 * m.z4 + y4 * m.w4,
			z1 * m.x4 + z2 * m.y4 + z3 * m.z4 + z4 * m.w4,
			w1 * m.x4 + w2 * m.y4 + w3 * m.z4 + w4 * m.w4
		);
	}
	void Matrix4::operator*=(const float& v)
	{
			x1 *= v, y1 *= v, z1 *= v, w1 *= v,
			x2 *= v, y2 *= v, z2 *= v, w2 *= v,
			x3 *= v, y3 *= v, z3 *= v, w3 *= v,
			x4 *= v, y4 *= v, z4 *= v, w4 *= v;
	}

	Matrix4 Matrix4::operator/(const float& v) const
	{
		return Matrix4
		(
			x1 / v, y1 / v, z1 / v, w1 / v,
			x2 / v, y2 / v, z2 / v, w2 / v,
			x3 / v, y3 / v, z3 / v, w3 / v,
			x4 / v, y4 / v, z4 / v, w4 / v
		);
	}

	Matrix4 Matrix4::Transpose() const
	{
		return Matrix4
		(
			x1, x2, x3, x4,
			y1, y2, y3, y4,
			z1, z2, z3, z4,
			w1, w2, w3, w4
		);
	}

	Matrix4 Matrix4::RotateX(const float AngleInDeg)
	{
		const float AngleInRad = Utilities::DegToRad(AngleInDeg);
		return Matrix4(1, 0, 0, 0,
			0, cos(AngleInRad), -sin(AngleInRad), 0,
			0, sin(AngleInRad), cos(AngleInRad), 0,
			0, 0, 0, 1);
	}


	Matrix4 Matrix4::RotateY(const float AngleInDeg)
	{
		const float AngleInRad = Utilities::DegToRad(AngleInDeg);
		return Matrix4(cos(AngleInRad), 0, sin(AngleInRad), 0,
			0, 1, 0, 0,
			-sin(AngleInRad), 0, cos(AngleInRad), 0,
			0, 0, 0, 1);

	}

	Matrix4 Matrix4::RotateZ(const float AngleInDeg)
	{
		const float AngleInRad = Utilities::DegToRad(AngleInDeg);
		return Matrix4(cos(AngleInRad), -sin(AngleInRad), 0, 0,
			sin(AngleInRad), cos(AngleInRad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	Matrix4 Matrix4::AxisRotation(Vector3 ArbitraryAxisDirectionVector, const Vector3 ArbitraryAxisPoint, const float AngleInDeg)
	{
		if (!ArbitraryAxisDirectionVector.CheckNormalized()) ArbitraryAxisDirectionVector.Normalize();

		const float A = ArbitraryAxisPoint.x;
		const float B = ArbitraryAxisPoint.y;
		const float C = ArbitraryAxisPoint.z;
		const float U = ArbitraryAxisDirectionVector.x;
		const float V = ArbitraryAxisDirectionVector.y;
		const float W = ArbitraryAxisDirectionVector.z;
		const float UPow2 = ArbitraryAxisDirectionVector.x * ArbitraryAxisDirectionVector.x;
		const float VPow2 = ArbitraryAxisDirectionVector.y * ArbitraryAxisDirectionVector.y;
		const float WPow2 = ArbitraryAxisDirectionVector.z * ArbitraryAxisDirectionVector.z;
		const float AngleInRad = Utilities::DegToRad(AngleInDeg);

		return Matrix4
		(
			UPow2 + (VPow2 + WPow2) * cos(AngleInRad), U * V * (1 - cos(AngleInRad)) - W * sin(AngleInRad), U * W * (1 - cos(AngleInRad)) + V * sin(AngleInRad), (A * (VPow2 + WPow2) - U * (B * V + C * W)) * (1 - cos(AngleInRad)) + (B * W - C * V) * sin(AngleInRad),
			U * V * (1 - cos(AngleInRad)) + W * sin(AngleInRad), VPow2 + (UPow2 + WPow2) * cos(AngleInRad), V * W * (1 - cos(AngleInRad)) - U * sin(AngleInRad), (B * (UPow2 + WPow2) - V * (A * U + C * W)) * (1 - cos(AngleInRad)) + (C * U - A * W) * sin(AngleInRad),
			U * W * (1 - cos(AngleInRad)) - V * sin(AngleInRad), V * W * (1 - cos(AngleInRad)) + U * sin(AngleInRad), WPow2 + (UPow2 + VPow2) * cos(AngleInRad), (C * (UPow2 + VPow2) - W * (A * U + B * V)) * (1 - cos(AngleInRad)) + (A * V - B * U) * sin(AngleInRad),
			0, 0, 0, 1
		);
	}

	Matrix4 Matrix4::Scale(float UniformScale)
	{
		return Matrix4(UniformScale, 0, 0, 0,
			0, UniformScale, 0, 0,
			0, 0, UniformScale, 0,
			0, 0, 0, 1);

	}
	Matrix4 Matrix4::Scale(Vector3 VectorScale)
	{
		return Matrix4(VectorScale.x, 0, 0, 0,
			0, VectorScale.y, 0, 0,
			0, 0, VectorScale.z, 0,
			0, 0, 0, 1);

	}

	Matrix4 Matrix4::Translate(float UniformTranslation)
	{
		return Matrix4(1, 0, 0, UniformTranslation,
			0, 1, 0, UniformTranslation,
			0, 0, 1, UniformTranslation,
			0, 0, 0, 1);
	}

	Matrix4 Matrix4::Translate(Vector3 VectorTranslation)
	{
		return Matrix4(1, 0, 0, VectorTranslation.x,
			0, 1, 0, VectorTranslation.y,
			0, 0, 1, VectorTranslation.z,
			0, 0, 0, 1);
	}

	void Matrix4::operator/=(const float& v)
	{
			x1 /= v, y1 /= v, z1 /= v, w1 /= v,
			x2 /= v, y2 /= v, z2 /= v, w2 /= v,
			x3 /= v, y3 /= v, z3 /= v, w3 /= v,
			x4 /= v, y4 /= v, z4 /= v, w4 /= v;
	}

	bool Matrix4::operator==(const Matrix4& m) const
	{
		return (m.x1 == x1 && m.x2 == x2 && m.x3 == x3 && m.x4 == x4 &&
				m.y1 == y1 && m.y2 == y2 && m.y3 == y3 && m.y4 == y4 &&
				m.z1 == z1 && m.z2 == z2 && m.z3 == z3 && m.z4 == z4 &&
				m.w1 == w1 && m.w2 == w2 && m.w3 == w3 && m.w4 == w4);
	}

