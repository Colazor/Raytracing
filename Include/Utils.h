#pragma once
#include <cmath>
#include <algorithm>


constexpr auto PI = 3.14159265358979323846264338f;
constexpr auto RATIO = 0.00555555555;
namespace Utilities
{
	inline const float DegToRad(const float Deg)
	{
		return (float)((Deg * PI) * RATIO);
	}
	inline float ClampValue(float maxV, float minV, float thisV)
	{
		if (thisV < minV) return minV;
		if (thisV > maxV) return maxV;
		return thisV;
	}

	template <typename T>
	inline void Swap(T& Val1, T& Val2)
	{
		T DummyVar = Val1;
		Val1 = Val2;
		Val2 = DummyVar;
	}


}
