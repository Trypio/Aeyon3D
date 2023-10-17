#ifndef AEYON3D_TRANSFORM_HPP
#define AEYON3D_TRANSFORM_HPP

#include "Component.hpp"
#include "Space.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace aeyon
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_position;
        glm::vec3 m_localPosition;

        glm::quat m_rotation;
        glm::quat m_localRotation;
        glm::vec3 m_eulerAngles;
        glm::vec3 m_localEulerAngles;

        glm::vec3 m_scale;
        glm::vec3 m_localScale;

		Transform* m_parent;
        std::vector<Transform*> m_children;

        glm::vec3 m_forward;
        glm::vec3 m_up;
        glm::vec3 m_right;

        glm::mat4x4 m_localToWorldMatrix;
        glm::mat4x4 m_worldToLocalMatrix;

        void recalculateMatrices();
        void recalculateDirections();
        void applyLocalChanges();

	public:
		Transform();

		void setPosition(const glm::vec3& position);
		void setLocalPosition(const glm::vec3& localPosition);
		void translate(const glm::vec3& translation);
		void translate(const glm::vec3& translation, Space relativeTo);

		void setRotation(const glm::quat& rotation);
        void setRotation(const glm::vec3& eulerAngles);
		void setLocalRotation(const glm::quat& rotation);
        void setLocalRotation(const glm::vec3& eulerAngles);
		void rotate(const glm::vec3& eulerAngles);
		void rotate(const glm::vec3& eulerAngles, Space relativeTo);
        void rotate(const glm::vec3& axis, float angle);
        void rotate(const glm::vec3& axis, float angle, Space relativeTo);
		void rotateAround(const glm::vec3& center, const glm::vec3& axis, float angle);

		void setLocalScale(const glm::vec3& localScale);
		void scale(const glm::vec3& scaling);

        void lookAt(const glm::vec3& target);
        void lookAt(const glm::vec3& target, const glm::vec3& worldUp);

        void setParent(Transform* parent);

		const glm::vec3& getPosition() const;
        const glm::vec3& getLocalPosition() const;

        const glm::quat& getRotation() const;
        const glm::quat& getLocalRotation() const;
        const glm::vec3& getEulerAngles() const;
        const glm::vec3& getLocalEulerAngles() const;

        const glm::vec3& getScale() const;
		const glm::vec3& getLocalScale() const;

		const glm::vec3& getForward() const;
		const glm::vec3& getRight() const;
		const glm::vec3& getUp() const;

		const glm::mat4x4& getLocalToWorldMatrix() const;
		const glm::mat4x4& getWorldToLocalMatrix() const;

		Transform* getParent() const;
        const std::vector<Transform*>& getChildren() const;

	};
}


#endif //AEYON3D_TRANSFORM_HPP
