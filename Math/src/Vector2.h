#pragma once
#include <cmath>

///
/// Entry class for some 2d math
///
class Vector2
{
public:		
	float x, y;
				
public:
	Vector2();
		
	Vector2(float x, float y);
        
	explicit Vector2(float v);
 
	Vector2 operator+(const Vector2& v) const;
		
	Vector2 operator-(const Vector2& v) const;
		
	Vector2 operator*(float value) const;
        
	Vector2 operator/(const float value) const;
				
	float operator *(const Vector2& vector) const;
		
	void operator+=(const Vector2& v);
				
	void operator-=(const Vector2& v);
		
	void operator*=(const float value);
		
	bool operator==(const Vector2& other) const;
		
	bool operator!=(const Vector2& other) const;
												
	float Dot(const Vector2& vector) const;
        
	float Cross(const Vector2& rhs) const;
		
	float Magnitude() const;
		
	float SquareMagnitude() const;
		
	void Trim(float size);
		
	void Normalize();
	Vector2 Unit() const;
   
	Vector2 Perpendicular() const;
		
	void Clear();
        
                
    /// Squared distance to another vector
	float SquareDistance(const Vector2& other) const;
        
    static Vector2 Zero;
};

inline Vector2 operator*(float val, const Vector2& rhs)
{
	return Vector2(rhs.x * val, rhs.y * val);
}
   