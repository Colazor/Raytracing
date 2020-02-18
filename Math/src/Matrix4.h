#pragma once 
#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
public:
	float x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4;
	Matrix4();

	Matrix4(const Vector4& c1, const Vector4& c2, const Vector4& c3, const Vector4& c4);

	Matrix4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4);
	Matrix4(float v);
	Matrix4 Identity() const;

	Matrix4 operator+(const Matrix4& m) const;
	void operator+=(const Matrix4& m);

	Matrix4 operator-(const Matrix4& m) const;

	void operator-=(const Matrix4& m);
	Vector4 operator*(const Vector4& v) const;
	Matrix4 operator*(const Matrix4& m) const;

	bool operator==(const Matrix4& m) const;
	void operator*=(const float& v);

	Matrix4 operator/(const float& v) const;

	Matrix4 Transpose() const;

	static Matrix4 RotateX(const float AngleInDeg);
	static Matrix4 RotateY(const float AngleInDeg);
	static Matrix4 RotateZ(const float AngleInDeg);

	static Matrix4 AxisRotation(Vector3 ArbitraryAxisDirectionVector, const Vector3 ArbitraryAxisPoint, const float AngleInDeg);

	static Matrix4 Scale(float UniformScale);
	static Matrix4 Scale(Vector3 VectorScale);

	static Matrix4 Translate(float UniformTranslation);

	static Matrix4 Translate(Vector3 VectorTranslation);

	void operator/=(const float& v);
};