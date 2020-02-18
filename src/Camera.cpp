#include "Camera.h"
#include "Utils.h"

Camera::Camera() : m_Position(), m_Forward(Vector3::UnitZ())
{
	m_Width = tan(Utilities::DegToRad(45));
	m_Height = m_Width;
	m_Up = Vector3(0, 1, 0);
	m_Right = m_Up.Cross(m_Forward);
}

Camera::Camera(Vector3 CameraPosition, Vector3 LookAt, Vector3 UpGuide, float FoV_DEG, float AspectRatio)
{
	m_Position = CameraPosition;
	m_Width = tan(Utilities::DegToRad(FoV_DEG));
	m_Height = m_Width / AspectRatio;


	Vector3* temp = new Vector3(LookAt - CameraPosition);
	temp->Normalize();
	m_Forward = *temp;
	delete temp;

	m_Up = UpGuide;

	m_Right = m_Up.Cross(m_Forward);

}

Ray Camera::ShootCameraRay(const Vector2* screenPos) const
{
	Vector3 Direction =  Vector3(m_Forward + (screenPos->x * m_Width * m_Right) + (screenPos->y * m_Height * m_Up));
	Direction.Normalize();
	return Ray(m_Position, Direction);
}