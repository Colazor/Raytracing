#include "Matrix3.h"

Matrix3::Matrix3() : x1(), y1(), z1(), x2(), y2(), z2(), x3(), y3(), z3() {};	

Matrix3::Matrix3(float v) : x1(v), y1(v), z1(v), x2(v), y2(v), z2(v), x3(v), y3(v), z3(v) {};

Matrix3::Matrix3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;

	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;

	this->z1 = z1;
	this->z2 = z2;
	this->z3 = z3;
};
