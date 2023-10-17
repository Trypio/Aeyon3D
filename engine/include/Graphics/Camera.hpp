#ifndef AEYON3D_CAMERA_HPP
#define AEYON3D_CAMERA_HPP

#include "Component.hpp"

namespace aeyon
{
    /**
     * A component that represents 3D camera properties.
     */
	class Camera : public Component
	{
	private:
		float m_nearClipPlane;
		float m_farClipPlane;
		float m_fieldOfView;

	public:
        Camera();

		void setNearClipPlane(float distance);
		void setFarClipPlane(float distance);
		void setFieldOfView(float degrees);

		float getNearClipPlane() const;
		float getFarClipPlane() const;
		float getFieldOfView() const;
	};
}


#endif //AEYON3D_CAMERA_HPP
