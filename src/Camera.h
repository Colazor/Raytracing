#pragma once
#include "..\..\Math\src\Vector2.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(Vector3 CameraPosition, Vector3 LookAt, Vector3 UpGuide, float FoV_DEG, float AspectRatio);

	Vector3 GetPosition() const { return m_Position; }
	Vector3 get_Forward() const { return m_Forward; }
	Vector3 get_Up() const { return m_Up; }
	Vector3 get_Right() const { return m_Right; }

	Ray ShootCameraRay(const Vector2* screenPos) const;

private:
	Vector3 m_Position, m_Forward, m_Up;
	Vector3 m_Right;
	float m_Width, m_Height;

};