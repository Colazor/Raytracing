#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
	float get_Multiplier() const
	{
		// Directional lights have no multiplier for the fade off since they hit from infinite distance
		return 1.0f;
	}
private:
};
