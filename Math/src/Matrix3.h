#pragma once 
#include "Vector3.h"

class Matrix3
{
public:
	float x1, y1, z1, x2, y2, z2, x3, y3, z3;
	Matrix3();
	explicit Matrix3(float v);
	Matrix3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
};