//
//
//

#ifndef AEYON3D_CAMERA_HPP
#define AEYON3D_CAMERA_HPP

#include "ECS/Component.hpp"

namespace aeyon
{
	class Camera : public Component<Camera>
	{
	private:
		float m_nearClipPlane = 0.1f;
		float m_farClipPlane = 100.0f;
		float m_fieldOfView = 45.0f;

	public:
		void setNearClipPlane(float distance);
		void setFarClipPlane(float distance);
		void setFieldOfView(float degrees);

		float getNearClipPlane() const;
		float getFarClipPlane() const;
		float getFieldOfView() const;
	};
}


#endif //AEYON3D_CAMERA_HPP
