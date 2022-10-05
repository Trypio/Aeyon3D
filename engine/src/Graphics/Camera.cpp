//
//
//

#include "Graphics/Camera.hpp"

namespace aeyon
{
	void Camera::setNearClipPlane(float distance)
	{
		m_nearClipPlane = distance;
	}

	void Camera::setFarClipPlane(float distance)
	{
		m_farClipPlane = distance;
	}

	void Camera::setFieldOfView(float degrees)
	{
		m_fieldOfView = degrees;
	}

	float Camera::getNearClipPlane() const
	{
		return m_nearClipPlane;
	}

	float Camera::getFarClipPlane() const
	{
		return m_farClipPlane;
	}

	float Camera::getFieldOfView() const
	{
		return m_fieldOfView;
	}
}